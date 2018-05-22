namespace USBFS_v3_20
{
    partial class CyBaseDescriptorPage
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
            System.ComponentModel.ComponentResourceManager resources = new System.ComponentModel.ComponentResourceManager(typeof(CyBaseDescriptorPage));
            System.Windows.Forms.ListViewGroup listViewGroup1 = new System.Windows.Forms.ListViewGroup("Audio Interfaces", System.Windows.Forms.HorizontalAlignment.Left);
            System.Windows.Forms.ListViewGroup listViewGroup2 = new System.Windows.Forms.ListViewGroup("Audio Control Descriptors (1.0)", System.Windows.Forms.HorizontalAlignment.Left);
            System.Windows.Forms.ListViewGroup listViewGroup3 = new System.Windows.Forms.ListViewGroup("Audio Streaming Descriptors (1.0)", System.Windows.Forms.HorizontalAlignment.Left);
            System.Windows.Forms.ListViewGroup listViewGroup4 = new System.Windows.Forms.ListViewGroup("Audio Control Descriptors (2.0)", System.Windows.Forms.HorizontalAlignment.Left);
            System.Windows.Forms.ListViewGroup listViewGroup5 = new System.Windows.Forms.ListViewGroup("Audio Streaming Descriptors (2.0)", System.Windows.Forms.HorizontalAlignment.Left);
            System.Windows.Forms.ListViewGroup listViewGroup6 = new System.Windows.Forms.ListViewGroup("MIDI Descriptors", System.Windows.Forms.HorizontalAlignment.Left);
            System.Windows.Forms.ListViewGroup listViewGroup7 = new System.Windows.Forms.ListViewGroup("Functional Descriptors", System.Windows.Forms.HorizontalAlignment.Left);
            System.Windows.Forms.ListViewGroup listViewGroup8 = new System.Windows.Forms.ListViewGroup("Endpoint Descriptors", System.Windows.Forms.HorizontalAlignment.Left);
            this.splitContainerReport = new System.Windows.Forms.SplitContainer();
            this.treeViewDesc = new System.Windows.Forms.TreeView();
            this.contextMenuStripTree = new System.Windows.Forms.ContextMenuStrip(this.components);
            this.renameToolStripMenuItem = new System.Windows.Forms.ToolStripMenuItem();
            this.imageList = new System.Windows.Forms.ImageList(this.components);
            this.panelCb = new System.Windows.Forms.Panel();
            this.toolStrip1 = new System.Windows.Forms.ToolStrip();
            this.toolStripButtonRemove = new System.Windows.Forms.ToolStripButton();
            this.toolStripSeparator1 = new System.Windows.Forms.ToolStripSeparator();
            this.toolStripButtonImport = new System.Windows.Forms.ToolStripButton();
            this.toolStripSplitButtonImport = new System.Windows.Forms.ToolStripSplitButton();
            this.fromFileToolStripMenuItem = new System.Windows.Forms.ToolStripMenuItem();
            this.toolStripMenuItemImportSeparator = new System.Windows.Forms.ToolStripSeparator();
            this.toolStripButtonSave = new System.Windows.Forms.ToolStripButton();
            this.splitContainerDetails = new System.Windows.Forms.SplitContainer();
            this.listViewDescList = new System.Windows.Forms.ListView();
            this.pictureBox1 = new System.Windows.Forms.PictureBox();
            this.labelListName = new System.Windows.Forms.Label();
            this.panel1 = new System.Windows.Forms.Panel();
            this.propertyGrid = new System.Windows.Forms.PropertyGrid();
            this.listViewPropGridErrors = new System.Windows.Forms.ListView();
            this.columnHeader1 = ((System.Windows.Forms.ColumnHeader)(new System.Windows.Forms.ColumnHeader()));
            this.labelItemProperties = new System.Windows.Forms.Label();
            this.panelDetails = new System.Windows.Forms.Panel();
            this.panelAddbtn = new System.Windows.Forms.Panel();
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
            this.panel1.SuspendLayout();
            this.panelDetails.SuspendLayout();
            this.panelAddbtn.SuspendLayout();
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
            this.splitContainerReport.Panel1.Controls.Add(this.treeViewDesc);
            this.splitContainerReport.Panel1.Controls.Add(this.panelCb);
            this.splitContainerReport.Panel1.Controls.Add(this.toolStrip1);
            // 
            // splitContainerReport.Panel2
            // 
            this.splitContainerReport.Panel2.Controls.Add(this.splitContainerDetails);
            this.splitContainerReport.Size = new System.Drawing.Size(775, 435);
            this.splitContainerReport.SplitterDistance = 310;
            this.splitContainerReport.SplitterWidth = 5;
            this.splitContainerReport.TabIndex = 0;
            // 
            // treeViewDesc
            // 
            this.treeViewDesc.AllowDrop = true;
            this.treeViewDesc.ContextMenuStrip = this.contextMenuStripTree;
            this.treeViewDesc.Dock = System.Windows.Forms.DockStyle.Fill;
            this.treeViewDesc.HideSelection = false;
            this.treeViewDesc.ImageIndex = 0;
            this.treeViewDesc.ImageList = this.imageList;
            this.treeViewDesc.LabelEdit = true;
            this.treeViewDesc.Location = new System.Drawing.Point(0, 25);
            this.treeViewDesc.Margin = new System.Windows.Forms.Padding(4);
            this.treeViewDesc.Name = "treeViewDesc";
            this.treeViewDesc.SelectedImageIndex = 0;
            this.treeViewDesc.Size = new System.Drawing.Size(306, 343);
            this.treeViewDesc.TabIndex = 2;
            this.treeViewDesc.BeforeLabelEdit += new System.Windows.Forms.NodeLabelEditEventHandler(this.treeViewDesc_BeforeLabelEdit);
            this.treeViewDesc.AfterLabelEdit += new System.Windows.Forms.NodeLabelEditEventHandler(this.treeViewDesc_AfterLabelEdit);
            this.treeViewDesc.ItemDrag += new System.Windows.Forms.ItemDragEventHandler(this.treeViewDesc_ItemDrag);
            this.treeViewDesc.AfterSelect += new System.Windows.Forms.TreeViewEventHandler(this.treeViewDesc_AfterSelect);
            this.treeViewDesc.DragDrop += new System.Windows.Forms.DragEventHandler(this.treeViewDesc_DragDrop);
            this.treeViewDesc.DragEnter += new System.Windows.Forms.DragEventHandler(this.treeViewDesc_DragEnter);
            this.treeViewDesc.DragOver += new System.Windows.Forms.DragEventHandler(this.treeViewDesc_DragOver);
            this.treeViewDesc.DragLeave += new System.EventHandler(this.treeViewDesc_DragLeave);
            this.treeViewDesc.Enter += new System.EventHandler(this.treeViewDesc_Enter);
            this.treeViewDesc.KeyDown += new System.Windows.Forms.KeyEventHandler(this.treeViewReport_KeyDown);
            this.treeViewDesc.MouseDown += new System.Windows.Forms.MouseEventHandler(this.treeViewDesc_MouseDown);
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
            this.imageList.Images.SetKeyName(6, "AudioHS.png");
            this.imageList.Images.SetKeyName(7, "Cable_Modem.png");
            this.imageList.Images.SetKeyName(8, "Configuration Refresh.ico");
            this.imageList.Images.SetKeyName(9, "Warning.png");
            this.imageList.Images.SetKeyName(10, "error.png");
            // 
            // panelCb
            // 
            this.panelCb.Dock = System.Windows.Forms.DockStyle.Bottom;
            this.panelCb.Location = new System.Drawing.Point(0, 368);
            this.panelCb.Margin = new System.Windows.Forms.Padding(4);
            this.panelCb.Name = "panelCb";
            this.panelCb.Size = new System.Drawing.Size(306, 63);
            this.panelCb.TabIndex = 5;
            // 
            // toolStrip1
            // 
            this.toolStrip1.GripStyle = System.Windows.Forms.ToolStripGripStyle.Hidden;
            this.toolStrip1.Items.AddRange(new System.Windows.Forms.ToolStripItem[] {
            this.toolStripButtonRemove,
            this.toolStripSeparator1,
            this.toolStripButtonImport,
            this.toolStripSplitButtonImport,
            this.toolStripButtonSave});
            this.toolStrip1.Location = new System.Drawing.Point(0, 0);
            this.toolStrip1.Name = "toolStrip1";
            this.toolStrip1.Size = new System.Drawing.Size(306, 25);
            this.toolStrip1.TabIndex = 1;
            this.toolStrip1.Text = "toolStrip";
            // 
            // toolStripButtonRemove
            // 
            this.toolStripButtonRemove.DisplayStyle = System.Windows.Forms.ToolStripItemDisplayStyle.Image;
            this.toolStripButtonRemove.Enabled = false;
            this.toolStripButtonRemove.Image = global::USBFS_v3_20.Properties.Resources.imdelete;
            this.toolStripButtonRemove.ImageTransparentColor = System.Drawing.Color.Magenta;
            this.toolStripButtonRemove.Name = "toolStripButtonRemove";
            this.toolStripButtonRemove.Size = new System.Drawing.Size(23, 22);
            this.toolStripButtonRemove.Text = "Delete";
            this.toolStripButtonRemove.Click += new System.EventHandler(this.toolStripButtonRemove_Click);
            // 
            // toolStripSeparator1
            // 
            this.toolStripSeparator1.Name = "toolStripSeparator1";
            this.toolStripSeparator1.Size = new System.Drawing.Size(6, 25);
            // 
            // toolStripButtonImport
            // 
            this.toolStripButtonImport.DisplayStyle = System.Windows.Forms.ToolStripItemDisplayStyle.Image;
            this.toolStripButtonImport.Image = global::USBFS_v3_20.Properties.Resources.imimport;
            this.toolStripButtonImport.ImageTransparentColor = System.Drawing.Color.Magenta;
            this.toolStripButtonImport.Name = "toolStripButtonImport";
            this.toolStripButtonImport.Size = new System.Drawing.Size(23, 22);
            this.toolStripButtonImport.Text = "Import Interface";
            this.toolStripButtonImport.Click += new System.EventHandler(this.toolStripButtonImport_Click);
            // 
            // toolStripSplitButtonImport
            // 
            this.toolStripSplitButtonImport.DisplayStyle = System.Windows.Forms.ToolStripItemDisplayStyle.Image;
            this.toolStripSplitButtonImport.DropDownItems.AddRange(new System.Windows.Forms.ToolStripItem[] {
            this.fromFileToolStripMenuItem,
            this.toolStripMenuItemImportSeparator});
            this.toolStripSplitButtonImport.Image = global::USBFS_v3_20.Properties.Resources.imimport;
            this.toolStripSplitButtonImport.ImageTransparentColor = System.Drawing.Color.Magenta;
            this.toolStripSplitButtonImport.Name = "toolStripSplitButtonImport";
            this.toolStripSplitButtonImport.Size = new System.Drawing.Size(32, 22);
            this.toolStripSplitButtonImport.Text = "Import Interface";
            this.toolStripSplitButtonImport.Click += new System.EventHandler(this.toolStripSplitButtonImport_Click);
            // 
            // fromFileToolStripMenuItem
            // 
            this.fromFileToolStripMenuItem.Name = "fromFileToolStripMenuItem";
            this.fromFileToolStripMenuItem.Size = new System.Drawing.Size(146, 24);
            this.fromFileToolStripMenuItem.Text = "From file...";
            this.fromFileToolStripMenuItem.Click += new System.EventHandler(this.fromFileToolStripMenuItem_Click);
            // 
            // toolStripMenuItemImportSeparator
            // 
            this.toolStripMenuItemImportSeparator.Name = "toolStripMenuItemImportSeparator";
            this.toolStripMenuItemImportSeparator.Size = new System.Drawing.Size(143, 6);
            // 
            // toolStripButtonSave
            // 
            this.toolStripButtonSave.DisplayStyle = System.Windows.Forms.ToolStripItemDisplayStyle.Image;
            this.toolStripButtonSave.Image = global::USBFS_v3_20.Properties.Resources.imsave;
            this.toolStripButtonSave.ImageTransparentColor = System.Drawing.Color.Magenta;
            this.toolStripButtonSave.Name = "toolStripButtonSave";
            this.toolStripButtonSave.Size = new System.Drawing.Size(23, 22);
            this.toolStripButtonSave.Text = "Save Interface";
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
            this.splitContainerDetails.Panel1.Controls.Add(this.listViewDescList);
            this.splitContainerDetails.Panel1.Controls.Add(this.pictureBox1);
            this.splitContainerDetails.Panel1.Controls.Add(this.labelListName);
            // 
            // splitContainerDetails.Panel2
            // 
            this.splitContainerDetails.Panel2.BackColor = System.Drawing.Color.LightSteelBlue;
            this.splitContainerDetails.Panel2.Controls.Add(this.panel1);
            this.splitContainerDetails.Panel2.Controls.Add(this.labelItemProperties);
            this.splitContainerDetails.Panel2.Controls.Add(this.panelDetails);
            this.splitContainerDetails.Size = new System.Drawing.Size(460, 435);
            this.splitContainerDetails.SplitterDistance = 185;
            this.splitContainerDetails.SplitterWidth = 5;
            this.splitContainerDetails.TabIndex = 0;
            // 
            // listViewDescList
            // 
            this.listViewDescList.Anchor = ((System.Windows.Forms.AnchorStyles)((((System.Windows.Forms.AnchorStyles.Top | System.Windows.Forms.AnchorStyles.Bottom) 
            | System.Windows.Forms.AnchorStyles.Left) 
            | System.Windows.Forms.AnchorStyles.Right)));
            listViewGroup1.Header = "Audio Interfaces";
            listViewGroup1.Name = "groupInterface";
            listViewGroup2.Header = "Audio Control Descriptors (1.0)";
            listViewGroup2.Name = "groupAC";
            listViewGroup3.Header = "Audio Streaming Descriptors (1.0)";
            listViewGroup3.Name = "groupAS";
            listViewGroup4.Header = "Audio Control Descriptors (2.0)";
            listViewGroup4.Name = "groupAC2";
            listViewGroup5.Header = "Audio Streaming Descriptors (2.0)";
            listViewGroup5.Name = "groupAS2";
            listViewGroup6.Header = "MIDI Descriptors";
            listViewGroup6.Name = "groupMS";
            listViewGroup7.Header = "Functional Descriptors";
            listViewGroup7.Name = "groupCommunications";
            listViewGroup8.Header = "Endpoint Descriptors";
            listViewGroup8.Name = "groupEndpoint";
            this.listViewDescList.Groups.AddRange(new System.Windows.Forms.ListViewGroup[] {
            listViewGroup1,
            listViewGroup2,
            listViewGroup3,
            listViewGroup4,
            listViewGroup5,
            listViewGroup6,
            listViewGroup7,
            listViewGroup8});
            this.listViewDescList.LargeImageList = this.imageList;
            this.listViewDescList.Location = new System.Drawing.Point(3, 34);
            this.listViewDescList.Margin = new System.Windows.Forms.Padding(4);
            this.listViewDescList.MultiSelect = false;
            this.listViewDescList.Name = "listViewDescList";
            this.listViewDescList.Size = new System.Drawing.Size(448, 142);
            this.listViewDescList.TabIndex = 11;
            this.listViewDescList.UseCompatibleStateImageBehavior = false;
            this.listViewDescList.SelectedIndexChanged += new System.EventHandler(this.listViewDescList_SelectedIndexChanged);
            // 
            // pictureBox1
            // 
            this.pictureBox1.Image = global::USBFS_v3_20.Properties.Resources.imcomponentadd;
            this.pictureBox1.Location = new System.Drawing.Point(8, 7);
            this.pictureBox1.Margin = new System.Windows.Forms.Padding(4);
            this.pictureBox1.Name = "pictureBox1";
            this.pictureBox1.Size = new System.Drawing.Size(16, 16);
            this.pictureBox1.SizeMode = System.Windows.Forms.PictureBoxSizeMode.AutoSize;
            this.pictureBox1.TabIndex = 10;
            this.pictureBox1.TabStop = false;
            // 
            // labelListName
            // 
            this.labelListName.AutoSize = true;
            this.labelListName.Font = new System.Drawing.Font("Tahoma", 9.75F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, ((byte)(204)));
            this.labelListName.ForeColor = System.Drawing.SystemColors.ControlText;
            this.labelListName.Location = new System.Drawing.Point(37, 7);
            this.labelListName.Margin = new System.Windows.Forms.Padding(4, 0, 4, 0);
            this.labelListName.Name = "labelListName";
            this.labelListName.Size = new System.Drawing.Size(126, 21);
            this.labelListName.TabIndex = 8;
            this.labelListName.Text = "Descriptors List";
            // 
            // panel1
            // 
            this.panel1.Anchor = ((System.Windows.Forms.AnchorStyles)((((System.Windows.Forms.AnchorStyles.Top | System.Windows.Forms.AnchorStyles.Bottom) 
            | System.Windows.Forms.AnchorStyles.Left) 
            | System.Windows.Forms.AnchorStyles.Right)));
            this.panel1.Controls.Add(this.propertyGrid);
            this.panel1.Controls.Add(this.listViewPropGridErrors);
            this.panel1.Location = new System.Drawing.Point(3, 27);
            this.panel1.Name = "panel1";
            this.panel1.Size = new System.Drawing.Size(450, 166);
            this.panel1.TabIndex = 2;
            // 
            // propertyGrid
            // 
            this.propertyGrid.Dock = System.Windows.Forms.DockStyle.Fill;
            this.propertyGrid.HelpVisible = false;
            this.propertyGrid.Location = new System.Drawing.Point(0, 0);
            this.propertyGrid.Margin = new System.Windows.Forms.Padding(4, 4, 4, 0);
            this.propertyGrid.Name = "propertyGrid";
            this.propertyGrid.PropertySort = System.Windows.Forms.PropertySort.Categorized;
            this.propertyGrid.Size = new System.Drawing.Size(450, 141);
            this.propertyGrid.TabIndex = 0;
            this.propertyGrid.ToolbarVisible = false;
            this.propertyGrid.PropertyValueChanged += new System.Windows.Forms.PropertyValueChangedEventHandler(this.propertyGrid_PropertyValueChanged);
            this.propertyGrid.SelectedObjectsChanged += new System.EventHandler(this.propertyGrid_SelectedObjectsChanged);
            // 
            // listViewPropGridErrors
            // 
            this.listViewPropGridErrors.Columns.AddRange(new System.Windows.Forms.ColumnHeader[] {
            this.columnHeader1});
            this.listViewPropGridErrors.Dock = System.Windows.Forms.DockStyle.Bottom;
            this.listViewPropGridErrors.HeaderStyle = System.Windows.Forms.ColumnHeaderStyle.None;
            this.listViewPropGridErrors.Location = new System.Drawing.Point(0, 141);
            this.listViewPropGridErrors.Name = "listViewPropGridErrors";
            this.listViewPropGridErrors.Size = new System.Drawing.Size(450, 25);
            this.listViewPropGridErrors.SmallImageList = this.imageList;
            this.listViewPropGridErrors.TabIndex = 7;
            this.listViewPropGridErrors.UseCompatibleStateImageBehavior = false;
            this.listViewPropGridErrors.View = System.Windows.Forms.View.Details;
            this.listViewPropGridErrors.Visible = false;
            // 
            // columnHeader1
            // 
            this.columnHeader1.Text = "";
            // 
            // labelItemProperties
            // 
            this.labelItemProperties.AutoSize = true;
            this.labelItemProperties.Font = new System.Drawing.Font("Tahoma", 9.75F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, ((byte)(204)));
            this.labelItemProperties.ForeColor = System.Drawing.SystemColors.ControlText;
            this.labelItemProperties.Location = new System.Drawing.Point(3, 4);
            this.labelItemProperties.Margin = new System.Windows.Forms.Padding(4, 0, 4, 0);
            this.labelItemProperties.Name = "labelItemProperties";
            this.labelItemProperties.Size = new System.Drawing.Size(167, 21);
            this.labelItemProperties.TabIndex = 9;
            this.labelItemProperties.Text = "Descriptor Properties";
            // 
            // panelDetails
            // 
            this.panelDetails.Anchor = ((System.Windows.Forms.AnchorStyles)((((System.Windows.Forms.AnchorStyles.Top | System.Windows.Forms.AnchorStyles.Bottom) 
            | System.Windows.Forms.AnchorStyles.Left) 
            | System.Windows.Forms.AnchorStyles.Right)));
            this.panelDetails.BackColor = System.Drawing.Color.Transparent;
            this.panelDetails.Controls.Add(this.panelAddbtn);
            this.panelDetails.Location = new System.Drawing.Point(3, 27);
            this.panelDetails.Margin = new System.Windows.Forms.Padding(4);
            this.panelDetails.Name = "panelDetails";
            this.panelDetails.Size = new System.Drawing.Size(450, 212);
            this.panelDetails.TabIndex = 1;
            // 
            // panelAddbtn
            // 
            this.panelAddbtn.BackColor = System.Drawing.SystemColors.Control;
            this.panelAddbtn.Controls.Add(this.buttonApply);
            this.panelAddbtn.Dock = System.Windows.Forms.DockStyle.Bottom;
            this.panelAddbtn.Location = new System.Drawing.Point(0, 174);
            this.panelAddbtn.Margin = new System.Windows.Forms.Padding(4);
            this.panelAddbtn.Name = "panelAddbtn";
            this.panelAddbtn.Size = new System.Drawing.Size(450, 38);
            this.panelAddbtn.TabIndex = 1;
            // 
            // buttonApply
            // 
            this.buttonApply.Location = new System.Drawing.Point(5, 4);
            this.buttonApply.Margin = new System.Windows.Forms.Padding(4);
            this.buttonApply.Name = "buttonApply";
            this.buttonApply.Size = new System.Drawing.Size(132, 31);
            this.buttonApply.TabIndex = 8;
            this.buttonApply.Text = "Add";
            this.buttonApply.UseVisualStyleBackColor = true;
            this.buttonApply.Click += new System.EventHandler(this.buttonApply_Click);
            // 
            // CyBaseDescriptorPage
            // 
            this.AutoScaleDimensions = new System.Drawing.SizeF(8F, 16F);
            this.AutoScaleMode = System.Windows.Forms.AutoScaleMode.Font;
            this.Controls.Add(this.splitContainerReport);
            this.Margin = new System.Windows.Forms.Padding(4);
            this.Name = "CyBaseDescriptorPage";
            this.Size = new System.Drawing.Size(775, 435);
            this.VisibleChanged += new System.EventHandler(this.CyBaseDescriptorPage_VisibleChanged);
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
            this.splitContainerDetails.Panel2.PerformLayout();
            this.splitContainerDetails.ResumeLayout(false);
            ((System.ComponentModel.ISupportInitialize)(this.pictureBox1)).EndInit();
            this.panel1.ResumeLayout(false);
            this.panelDetails.ResumeLayout(false);
            this.panelAddbtn.ResumeLayout(false);
            this.ResumeLayout(false);

        }

        #endregion

        private System.Windows.Forms.SplitContainer splitContainerReport;
        private System.Windows.Forms.ToolStrip toolStrip1;
        private System.Windows.Forms.SplitContainer splitContainerDetails;
        private System.Windows.Forms.ImageList imageList;
        private System.Windows.Forms.TreeView treeViewDesc;
        private System.Windows.Forms.Panel panelDetails;
        private System.Windows.Forms.Label labelListName;
        private System.Windows.Forms.ToolStripButton toolStripButtonRemove;
        private System.Windows.Forms.Label labelItemProperties;
        private System.Windows.Forms.ToolTip toolTipList;
        private System.Windows.Forms.PictureBox pictureBox1;
        private System.Windows.Forms.PropertyGrid propertyGrid;
        private System.Windows.Forms.Panel panelAddbtn;
        private System.Windows.Forms.Button buttonApply;
        private System.Windows.Forms.ToolStripButton toolStripButtonImport;
        private System.Windows.Forms.ToolStripButton toolStripButtonSave;
        private System.Windows.Forms.ToolStripSeparator toolStripSeparator1;
        protected System.Windows.Forms.Panel panelCb;
        private System.Windows.Forms.ContextMenuStrip contextMenuStripTree;
        private System.Windows.Forms.ToolStripMenuItem renameToolStripMenuItem;
        private System.Windows.Forms.ToolStripMenuItem fromFileToolStripMenuItem;
        private System.Windows.Forms.ToolStripSplitButton toolStripSplitButtonImport;
        private System.Windows.Forms.ToolStripSeparator toolStripMenuItemImportSeparator;
        protected System.Windows.Forms.ListView listViewDescList;
        private System.Windows.Forms.Panel panel1;
        private System.Windows.Forms.ListView listViewPropGridErrors;
        private System.Windows.Forms.ColumnHeader columnHeader1;
    }
}
