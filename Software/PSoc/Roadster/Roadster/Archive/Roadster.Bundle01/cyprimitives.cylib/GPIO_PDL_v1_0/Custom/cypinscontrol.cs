/*******************************************************************************
* Copyright 2008-2016, Cypress Semiconductor Corporation.  All rights reserved.
* You may use this file only in accordance with the license, terms, conditions, 
* disclaimers, and limitations in the end user license agreement accompanying 
* the software package with which this file was provided.
********************************************************************************/

using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Drawing;
using System.Drawing.Imaging;
using System.IO;
using System.Linq;
using System.Windows.Forms;
using System.Diagnostics;
using System.Diagnostics.CodeAnalysis;
using System.Windows.Forms.Design;

using CyDesigner.Common.Base.Controls;
using CyDesigner.Extensions.Common;

using ActiproSoftware.UIStudio.TabStrip;

namespace Cypress.Comps.PinsAndPorts.GPIO_PDL_v1_0
{
    /// <summary>
    /// Contains a SplitContainer with a tree on the left and params on the right.
    /// </summary>
    [ExcludeFromCodeCoverage]
    public partial class CyPinsControl : UserControl, ICyParamEditingControl
    {
        internal static readonly Formal.ErrorKey[] OwnedSettings = new Formal.ErrorKey[]
        {
            Formal.ErrorKey.DISPLAY_AS_BUS,
        };

        private readonly CyPinData m_port;
        private readonly CyErrorManager m_errMgr;
        private readonly int PinImageIndex;
        private readonly int SIOPinImageIndex;

        private CyNumPinsToolStripTextBox m_numPinsTextBox;
        private ToolStripCheckBox m_displayAsBusCheckBox;
        private ToolStripButton m_moveUpButton;
        private ToolStripButton m_moveDownButton;
        private ToolStripButton m_deleteButton;
        private ToolStripButton m_renameButton;
        private ToolStripButton m_groupSIOButton;
        private ToolStripButton m_ungroupSIOButton;

        private const int DefaultMaxPinCount = 64;
        private const int AllPinsTag = -2;
        private const int SIOPairTag = -3;
        private CyPerPinDataControl m_perPinDataControl;
        // Controls that break forms designer
        private CyPinPicture m_pinPicture;
        private CyDesigner.Common.Base.Controls.CyMultiSelectTreeView m_treeView;

        public CyPinsControl(CyDeviceSupport deviceSupport, CyErrorManager errMgr, CyPinData pins)
        {
            InitializeComponent();
            InitPinPicture();
            InitTreeView();

            m_port = pins;
            m_errMgr = errMgr;
            Dock = DockStyle.Fill;

            m_treeView.CheckBoxes = CyTreeView.CheckBoxDisplay.SHOW_NONE;
            m_treeView.ShowRootLines = false;
            m_treeView.HideSelection = false;
            m_treeView.ShowNodeToolTips = true;
            m_treeView.ImageList = new CyTableViewBase.CyImageList();
            PinImageIndex = m_treeView.ImageList.AddImage(Resource1.PinImage);
            SIOPinImageIndex = m_treeView.ImageList.AddImage(Resource1.SIOPinImage);

            m_toolStrip.CanOverflow = true;
            m_toolStrip.GripStyle = ToolStripGripStyle.Hidden;
            m_toolStrip.RenderMode = ToolStripRenderMode.System;
            m_toolStrip.ShowItemToolTips = true;

            ToolStripLabel numPinsLabel = new ToolStripLabel(Resource1.Prompt_NumberOfPins);
            m_toolStrip.Items.Add(numPinsLabel);

            int maxPins = deviceSupport.MaxPinCount;
            if (maxPins < 0) maxPins = DefaultMaxPinCount;
            m_numPinsTextBox = new CyNumPinsToolStripTextBox(pins, maxPins);
            m_toolStrip.Items.Add(m_numPinsTextBox);
            m_toolStrip.Items.Add(new ToolStripSeparator());

            m_displayAsBusCheckBox = new ToolStripCheckBox();
            m_displayAsBusCheckBox.Text = Resource1.DisplayAsBus;
            m_toolStrip.Items.Add(m_displayAsBusCheckBox);
            m_toolStrip.Items.Add(new ToolStripSeparator());

            m_deleteButton = 
                new ToolStripButton(Resource1.Cmd_DeletePin, Resource1.DeleteImage, DeletePinClicked);
            m_deleteButton.DisplayStyle = ToolStripItemDisplayStyle.Image;
            m_toolStrip.Items.Add(m_deleteButton);

            m_renameButton = 
                new ToolStripButton(Resource1.Cmd_ChangeAlias, Resource1.PinAliasImage, RenamePinClicked);
            m_renameButton.DisplayStyle = ToolStripItemDisplayStyle.Image;
            m_toolStrip.Items.Add(m_renameButton);

            m_moveUpButton = new ToolStripButton(Resource1.Cmd_MovePinUp, Resource1.MoveUpImage, MovePinUpClicked);
            m_moveUpButton.DisplayStyle = ToolStripItemDisplayStyle.Image;
            m_toolStrip.Items.Add(m_moveUpButton);

            m_moveDownButton =
                new ToolStripButton(Resource1.Cmd_MovePinDown, Resource1.MoveDownImage, MovePinDownClicked);
            m_moveDownButton.DisplayStyle = ToolStripItemDisplayStyle.Image;
            m_toolStrip.Items.Add(m_moveDownButton);

            ToolStripSeparator sioSeparator = new ToolStripSeparator();
            m_toolStrip.Items.Add(sioSeparator);

            m_groupSIOButton = new ToolStripButton(Resource1.Cmd_PairSelectedSIOs, Resource1.PairSIOsImage,
                (o, e) => SetSioGroup(true));
            m_groupSIOButton.DisplayStyle = ToolStripItemDisplayStyle.Image;
            m_toolStrip.Items.Add(m_groupSIOButton);

            m_ungroupSIOButton = new ToolStripButton(Resource1.Cmd_UnpairSelectedSIOs, Resource1.UnpairSIOsImage,
                (o, e) => SetSioGroup(false));
            m_ungroupSIOButton.DisplayStyle = ToolStripItemDisplayStyle.Image;
            m_toolStrip.Items.Add(m_ungroupSIOButton);
            m_toolStrip.Items.Add(new ToolStripSeparator());

            if (!deviceSupport.HasSIO)
            {
                // These buttons have been added to be compatible with the expectation of future availability
                // but they are hidden until SIO is supported.
                m_groupSIOButton.Visible = m_ungroupSIOButton.Visible = sioSeparator.Visible = false;
            }

            m_perPinDataControl = new CyPerPinDataControl(deviceSupport, errMgr, pins, m_pinPicture, () => RebuildTree());
            m_perPinDataControl.Dock = DockStyle.Fill;
            m_perPinDataControl.TabStripSelectionChanged += m_perPinControl_TabStripSelectedIndexChanged;
            m_splitContainer.Panel2.Controls.Add(m_perPinDataControl);

            RebuildTree();
            UpdateMinSize();
            UpdateData();
            UpdatePerPinDataDisplayed();

            m_treeView.BeforeCollapse += m_treeView_BeforeCollapse;
            m_treeView.AfterMultiSelect += m_treeView_AfterMultiSelect;
            m_treeView.NodeMouseDoubleClick += m_treeView_NodeMouseDoubleClick;
            m_numPinsTextBox.Validated += m_numPinsTextBox_Validated;
            m_displayAsBusCheckBox.CheckedChanged += m_displayAsBusCheckBox_CheckedChanged;

            errMgr.RegisterKeyOwner(Formal.ErrorKey.DISPLAY_AS_BUS, m_errorProvider, m_displayAsBusCheckBox);
        }

        private void InitTreeView()
        {
            ComponentResourceManager resources = new ComponentResourceManager(typeof(CyPinsControl));
            m_treeView = new CyMultiSelectTreeView();
            m_treeView.BackColor = System.Drawing.SystemColors.Window;
            m_treeView.CheckBoxes = CyDesigner.Common.Base.Controls.CyTreeView.CheckBoxDisplay.SHOW_NONE;
            m_treeView.CyTreeViewNodeSorter = null;
            m_treeView.Dock = System.Windows.Forms.DockStyle.Fill;
            m_treeView.FocusWhenSelectedNodeChanged = false;
            m_treeView.Font = new System.Drawing.Font("Microsoft Sans Serif", 7.8F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, ((byte)(0)));
            m_treeView.ForeColor = System.Drawing.SystemColors.WindowText;
            m_treeView.FullRowSelect = false;
            m_treeView.HideSelection = true;
            m_treeView.HotTracking = false;
            m_treeView.HotTrackingFont = new System.Drawing.Font("Microsoft Sans Serif", 7.8F, System.Drawing.FontStyle.Underline);
            m_treeView.HotTrackingForeColor = System.Drawing.SystemColors.HotTrack;
            m_treeView.ImageIndex = -1;
            m_treeView.ImageKey = null;
            CyTableViewBase.CyImageList cyImageList1 = new CyTableViewBase.CyImageList();
            cyImageList1.ImageSize = new System.Drawing.Size(16, 16);
            m_treeView.ImageList = cyImageList1;
            m_treeView.Indent = 19;
            m_treeView.ItemHeight = 18;
            m_treeView.LineColor = System.Drawing.SystemColors.GrayText;
            m_treeView.Location = new System.Drawing.Point(0, 0);
            m_treeView.MakeId = ((CyTreeView.MakeUniqueIdDelegate)(resources.GetObject("m_treeView.MakeId")));
            m_treeView.Name = "m_treeView";
            m_treeView.PathSeperator = "\\";
            m_treeView.Scrollable = true;
            m_treeView.SelectedNode = null;
            m_treeView.ShowHorizontalScrollBar = true;
            m_treeView.ShowLines = true;
            m_treeView.ShowNodeToolTips = false;
            m_treeView.ShowPlusMinus = true;
            m_treeView.ShowRootLines = true;
            m_treeView.Size = new Size(136, 286);
            m_treeView.Sorted = false;
            m_treeView.TabIndex = 0;
            m_treeView.TabStop = false;
            m_treeView.Text = "cyTreeView1";

            m_splitContainer1.SuspendLayout();
            m_splitContainer1.Panel1.SuspendLayout();
            m_splitContainer1.Panel1.Controls.Add(m_treeView);
            m_splitContainer1.Panel1.ResumeLayout(false);
            m_splitContainer1.Panel1.PerformLayout();
            m_splitContainer1.ResumeLayout(false);
        }

        private void InitPinPicture()
        {
            // Can't initialize CyPinPicture from designer.cs; forms designer chokes trying to instantiate it
            m_pinPicture = new CyPinPicture();
            ((ISupportInitialize)(m_pinPicture)).BeginInit();
            this.m_pinPicture.BackColor = System.Drawing.Color.White;
            this.m_pinPicture.BorderStyle = BorderStyle.None;
            this.m_pinPicture.Name = "m_pinPicture";
            this.m_pinPicture.ShowAnalog = false;
            this.m_pinPicture.ShowBidirectional = false;
            this.m_pinPicture.ShowDigitalInput = false;
            this.m_pinPicture.ShowDigitalInputConnection = false;
            this.m_pinPicture.ShowDigitalOutput = false;
            this.m_pinPicture.ShowDigitalOutputConnection = false;
            this.m_pinPicture.ShowOutputEnable = false;
            this.m_pinPicture.ShowAnnotation = false;
            this.m_pinPicture.Size = new System.Drawing.Size(180, 90);
            this.m_pinPicture.TabIndex = 8;
            this.m_pinPicture.TabStop = false;
            ((System.ComponentModel.ISupportInitialize)(this.m_pinPicture)).EndInit();
            m_splitContainer1.SuspendLayout();
            m_splitContainer1.Panel2.SuspendLayout();
            m_splitContainer1.Panel2.Controls.Add(m_pinPicture);
            m_splitContainer1.Panel2.ResumeLayout(false);
            m_splitContainer1.Panel2.PerformLayout();
            m_splitContainer1.ResumeLayout(false);
        }

        private void PerformDispose()
        {
            m_treeView.BeforeCollapse -= m_treeView_BeforeCollapse;
            m_treeView.AfterMultiSelect -= m_treeView_AfterMultiSelect;
            m_treeView.NodeMouseDoubleClick -= m_treeView_NodeMouseDoubleClick;
            m_numPinsTextBox.Validated -= m_numPinsTextBox_Validated;
        }

        void m_perPinControl_TabStripSelectedIndexChanged(object sender, EventArgs args)
        {
            UpdateMinSize();
        }

        void UpdateMinSize()
        {
            const int LEFT_PANE_SIZE = 185; // 5 px for borders, 180 for content
            Size minSize = m_perPinDataControl.GetPreferredSize(Size.Empty);
            minSize.Width += LEFT_PANE_SIZE;
            minSize.Height = Math.Max(minSize.Height, m_splitContainer.MinimumSize.Height);
            AutoScrollMinSize = minSize;
        }

        void m_treeView_AfterMultiSelect(object sender, CyMultiSelectTreeViewEventArgs e)
        {
            //The event is raised twice as part of setting the selection. Once to clear the selection and again to 
            //set the selected items. The first call needs to be ignored.
            if (m_treeView.SelectedNodesCount > 0)
            {
                UpdateToolStripItemsEnabled();
                UpdatePerPinDataDisplayed();
            }
        }

        static void m_treeView_BeforeCollapse(object sender, CyTreeViewCancelEventArgs e)
        {
            //Don't allow the root node to be collapsed
            if (e.Action == CyTreeViewAction.Collapse && e.Node.FullPath.Equals(Resource1.AllPins))
                e.Cancel = true;
        }

        public void UpdateData()
        {
            // Force cache reloads
            m_port.DisplayAsBusChanged();
            m_port.PinCountChanged();
            m_displayAsBusCheckBox.Checked = m_port.DisplayAsBus;
            m_numPinsTextBox.Text = m_port.PinCount.ToString();

            List<int> selectedPinIndexes = GetPinIndexes(m_treeView.SelectedNodes);
            IList<CyPinData.PerPin> selectedPins = GetSelectedPins(selectedPinIndexes);
            m_perPinDataControl.UpdateData(selectedPins);
            UpdateToolStripItemsEnabled();
            RebuildTree();
        }

        public void RebuildTree()
        {
            m_treeView.SuspendLayout();
            m_treeView.BeginUpdate();

            IEnumerable<int> prevSelectedIndexes = GetPinIndexes(m_treeView.SelectedNodes);
            m_treeView.Nodes.Clear();

            //Need to create [All Pins] node, SIO Pair nodes, SIO nodes, and pin nodes.
            CyTreeNode rootNode = new CyTreeNode(Resource1.AllPins);
            rootNode.Tag = AllPinsTag;

            CyTreeNode sioGroupNode = null;
            for (int i = 0; i < m_port.PinCount; i++)
            {
                CyTreeNode leafNode = new CyTreeNode(m_port.GetPinPoundDefineName(i));
                leafNode.Tag = i; //the tag stores the pin index

                if (!m_port[i].RequiresSIO)
                {
                    leafNode.ImageIndex = PinImageIndex;
                    rootNode.Nodes.Add(leafNode);
                }
                else if (!m_port[i].IsPairedSio)
                {
                    leafNode.ImageIndex = SIOPinImageIndex;
                    rootNode.Nodes.Add(leafNode);
                }
                else
                {
                    if (null == sioGroupNode || sioGroupNode.Nodes.Count == 2)
                    {
                        sioGroupNode = new CyTreeNode(Resource1.SIOPair);
                        sioGroupNode.Tag = SIOPairTag;
                        rootNode.Nodes.Add(sioGroupNode);
                    }

                    leafNode.ImageIndex = SIOPinImageIndex;
                    sioGroupNode.Nodes.Add(leafNode);
                }
            }

            m_treeView.Nodes.Add(rootNode);

            SelectPins(prevSelectedIndexes);
            if (m_treeView.SelectedNodesCount == 0)
                m_treeView.SelectedNodes = new CyTreeNode[] { rootNode };

            m_treeView.EndUpdate();
            m_treeView.ResumeLayout();
        }

        static int GetPinIndex(CyTreeNode node)
        {
            if (node != null)
            {
                Debug.Assert(node.Tag is int);
                return (int)node.Tag;
            }
            return -1;
        }

        List<int> GetPinIndexes(IEnumerable<CyTreeNode> nodes)
        {
            List<int> indexes = new List<int>();

            foreach (CyTreeNode node in nodes)
            {
                if (node != null)
                {
                    Debug.Assert(node.Tag is int);
                    int tagInt = (int)node.Tag;

                    if (tagInt == AllPinsTag)
                    {
                        for (int i = 0; i < m_port.PinCount; i++)
                        {
                            if (!indexes.Contains(i))
                                indexes.Add(i);
                        }
                        break;
                    }
                    else if (tagInt == SIOPairTag)
                    {
                        foreach (CyTreeNode childNode in node.Nodes)
                        {
                            int childIndex = GetPinIndex(childNode);
                            if (!indexes.Contains(childIndex))
                                indexes.Add(childIndex);
                        }
                    }
                    else if (!indexes.Contains(tagInt))
                        indexes.Add(tagInt);
                }
            }

            return indexes;
        }

        private void SelectPin(int index)
        {
            if (index >= 0)
            {
                foreach (CyTreeNode node in m_treeView.GetAllNodesInTree())
                {
                    int nodesPinIndex = GetPinIndex(node);
                    if (nodesPinIndex == index)
                    {
                        m_treeView.SelectedNodes = new CyTreeNode[] { node };
                        return;
                    }
                }
            }

            //Select the root node if the selection failed
            Debug.Assert(m_treeView.Nodes.Count == 1);
            m_treeView.SelectedNodes = new CyTreeNode[] { m_treeView.Nodes[0] };
        }

        private void SelectPins(IEnumerable<int> indexes)
        {
            List<CyTreeNode> nodes = new List<CyTreeNode>();
            foreach (int index in indexes)
            {
                if (index >= 0)
                {
                    foreach (CyTreeNode node in m_treeView.GetAllNodesInTree())
                        if (index == GetPinIndex(node)) nodes.Add(node);
                }
            }

            if (nodes.Count == 0)
            {
                //Select the root node if the selection failed
                Debug.Assert(m_treeView.Nodes.Count == 1);
                m_treeView.SelectedNodes = new CyTreeNode[] { m_treeView.Nodes[0] };
            }
            else
            {
                m_treeView.SelectedNodes = nodes;
            }
        }

        CyTreeNode GetAssociatedNode(int index)
        {
            CyTreeNode node = m_treeView.GetAllNodesInTree().FirstOrDefault(n => index == GetPinIndex(n));
            return node;
        }

        private IList<CyPinData.PerPin> GetSelectedPins(IList<int> pinIndexes)
        {
            CyPinData.PerPin[] pins = new CyPinData.PerPin[pinIndexes.Count];
            for (int i = 0; i < pinIndexes.Count; i++)
                pins[i] = m_port[pinIndexes[i]];
            return pins;
        }

        void m_displayAsBusCheckBox_CheckedChanged(object sender, EventArgs e)
        {
            m_port.DisplayAsBus = m_displayAsBusCheckBox.Checked;
        }

        #region Per Pin Data

        private void UpdatePerPinDataDisplayed()
        {
            List<int> selectedPinIndexes = GetPinIndexes(m_treeView.SelectedNodes);
            IList<CyPinData.PerPin> selectedPins = GetSelectedPins(selectedPinIndexes);
            m_perPinDataControl.UpdateData(selectedPins);

            m_perPinDataControl.InputTabEnabled =
                selectedPins.Any(pin => pin.Type.IsOneOf(CyPinType.Bidirectional | CyPinType.Digital_In));
            m_perPinDataControl.OutputTabEnabled =
                selectedPins.Any(pin => pin.Type.IsOneOf(CyPinType.Bidirectional | CyPinType.Digital_Out));
        }

        #endregion

        #region ToolStrip Handlers

        private void UpdateToolStripItemsEnabled()
        {
            m_deleteButton.Enabled = false;
            m_renameButton.Enabled = false;
            m_moveUpButton.Enabled = false;
            m_moveDownButton.Enabled = false;
            m_groupSIOButton.Enabled = false;
            m_ungroupSIOButton.Enabled = false;

            m_displayAsBusCheckBox.ToolTipText = Resource1.Msg_MustBeHomogenous;
            m_groupSIOButton.ToolTipText = Resource1.Msg_CannotPairSIOs;
            m_deleteButton.ToolTipText = string.Empty;

            List<int> selectedPinIndexes = GetPinIndexes(m_treeView.SelectedNodes);
            if (selectedPinIndexes.Count > 0)
            {
                if (selectedPinIndexes.Count == 1)
                {
                    m_renameButton.Enabled = true;
                }
                else if (selectedPinIndexes.Count == 2)
                {
                    int index1 = Math.Min(selectedPinIndexes[0], selectedPinIndexes[1]);
                    int index2 = Math.Max(selectedPinIndexes[0], selectedPinIndexes[1]);

                    CyPinData.PerPin pin1 = m_port[index1];
                    CyPinData.PerPin pin2 = m_port[index2];

                    //If adjacent and both are SIOs then they can be paired or unpaired
                    if ((index2 - index1) == 1 && pin1.RequiresSIO && pin2.RequiresSIO)
                    {
                        if (pin1.SioPair_1of2 && pin2.SioPair_2of2)
                            m_ungroupSIOButton.Enabled = true;
                        else if (!pin1.IsPairedSio && !pin2.IsPairedSio)
                        {
                            m_groupSIOButton.Enabled = true;
                            m_groupSIOButton.ToolTipText = string.Empty;
                        }
                    }
                }

                int numLeafNodes = m_treeView.GetAllNodesInTree().Count(node => node.Nodes.Count == 0);
                m_deleteButton.Enabled = numLeafNodes - selectedPinIndexes.Count > 0;
                m_deleteButton.ToolTipText = m_deleteButton.Enabled ? "" : Resource1.Msg_CannotDeleteSelectedPin;

                //otherwise already as low as it can go
                m_moveDownButton.Enabled = !selectedPinIndexes.Contains(numLeafNodes - 1);

                //otherwise already as high as it can go
                m_moveUpButton.Enabled = !selectedPinIndexes.Contains(0);
            }
        }

        protected override bool ProcessCmdKey(ref Message msg, Keys keyData)
        {
            if (m_treeView.ContainsFocus)
            {
                switch (keyData)
                {
                    case Keys.F2:
                        m_renameButton.PerformClick();
                        break;

                    case Keys.Delete:
                        m_deleteButton.PerformClick();
                        break;

                    case Keys.Control | Keys.A:
                        m_treeView.SelectAll();
                        break;
                }
            }
            return base.ProcessCmdKey(ref msg, keyData);
        }

        void m_treeView_NodeMouseDoubleClick(object sender, CyTreeNodeMouseClickEventArgs e)
        {
            m_renameButton.PerformClick();
        }

        void m_numPinsTextBox_Validated(object sender, EventArgs e)
        {
            RebuildTree();
        }

        void RenamePinClicked(object sender, EventArgs e)
        {
            Debug.Assert(m_treeView.SelectedNodesCount == 1);
            int pinIndex = GetPinIndex(m_treeView.SelectedNode);

            if (pinIndex >= 0)
            {
                CyTreeNode node = GetAssociatedNode(pinIndex);
                if (node != null)
                {
                    using (CyPinAliasDialog dialog = new CyPinAliasDialog(node.Text, m_port[pinIndex].Alias, pinIndex))
                    {
                        Form parent = this.FindForm();
                        if (dialog.ShowDialog(parent) == DialogResult.OK)
                        {
                            m_port[pinIndex].Alias = dialog.Alias;
                            node.Text = m_port.GetPinPoundDefineName(pinIndex);
                        }
                    }
                }
                else
                    Debug.Fail("Could not find node");
            }
            else
                Debug.Fail("Invalid node selected for rename");
        }

        void DeletePinClicked(object sender, EventArgs e)
        {
            List<int> selectedPinIndexes = GetPinIndexes(m_treeView.SelectedNodes);
            Debug.Assert(selectedPinIndexes.Count >= 1);

            selectedPinIndexes.Sort();
            for (int i = selectedPinIndexes.Count - 1; i >= 0; i--)
                m_port.DeletePin(selectedPinIndexes[i]);

            m_numPinsTextBox.Text = m_port.PinCount.ToString();
            RebuildTree();
        }

        void MovePinUpClicked(object sender, EventArgs e)
        {
            List<int> selectedPinIndexes = GetPinIndexes(m_treeView.SelectedNodes);
            Debug.Assert(selectedPinIndexes.Count >= 1);

            selectedPinIndexes.Sort();
            List<int> newSelectedPins = new List<int>();
            foreach (int i in selectedPinIndexes)
                newSelectedPins.Add(i - 1);

            for (int i = 0; i < selectedPinIndexes.Count; i++)
                m_port.MoveUp(selectedPinIndexes[i]);

            RebuildTree();
            SelectPins(newSelectedPins);
        }

        void MovePinDownClicked(object sender, EventArgs e)
        {
            List<int> selectedPinIndexes = GetPinIndexes(m_treeView.SelectedNodes);
            Debug.Assert(selectedPinIndexes.Count >= 1);

            selectedPinIndexes.Sort();
            List<int> newSelectedPins = new List<int>();
            foreach (int i in selectedPinIndexes)
                newSelectedPins.Add(i + 1);

            for (int i = selectedPinIndexes.Count - 1; i >= 0; i--)
                m_port.MoveDown(selectedPinIndexes[i]);

            RebuildTree();
            SelectPins(newSelectedPins);
        }

        void SetSioGroup(bool pairUp)
        {
            List<int> selectedPinIndexes = GetPinIndexes(m_treeView.SelectedNodes);
            Debug.Assert(selectedPinIndexes.Count == 2);
            m_port.MakePair(selectedPinIndexes[0], selectedPinIndexes[1], pairUp);
            RebuildTree();
        }

        #endregion

        #region ICyParamEditingControl Members

        public Control DisplayControl
        {
            get { return this; }
        }

        public IEnumerable<CyCustErr> GetErrors()
        {
            foreach (string errMsg in m_errMgr.GetErrors(OwnedSettings))
                yield return new CyCustErr(errMsg);
            foreach (string errMsg in m_errMgr.GetErrors(CyGeneralControl.OwnedSettings))
                yield return new CyCustErr(errMsg);
            foreach (string errMsg in m_errMgr.GetErrors(CyInputControl.OwnedSettings))
                yield return new CyCustErr(errMsg);
            foreach (string errMsg in m_errMgr.GetErrors(CyOutputControl.OwnedSettings))
                yield return new CyCustErr(errMsg);
        }

        #endregion
    }

    [ExcludeFromCodeCoverage]
    public class CyNumPinsToolStripTextBox : ToolStripTextBox
    {
        CyPinData m_port;
        int m_maxPinCount;

        public CyNumPinsToolStripTextBox(CyPinData port, int maxPinCount)
        {
            m_port = port;
            m_maxPinCount = maxPinCount;
        }

        public override Size GetPreferredSize(Size constrainingSize)
        {
            Size size = base.GetPreferredSize(constrainingSize);
            size.Width = 40;
            return size;
        }

        protected override void OnValidating(CancelEventArgs e)
        {
            byte pinCount;
            string errMsg = string.Empty;
            if (byte.TryParse(Text, out pinCount))
            {
                if (pinCount < 1 || pinCount > m_maxPinCount)
                    errMsg = string.Format(Resource1.Err_PinCountOutOfRange, m_maxPinCount);
                else if (pinCount > CyPinData.PINS_PER_PORT)
                {
                    int pinsToCheck = Math.Min((byte)CyPinData.PINS_PER_PORT, m_port.PinCount);
                    if (m_port.Pins.Take(pinsToCheck).Any(pin => pin.InputInterrupt != CyInputInterruptTrigger.None))
                        errMsg = Resource1.Err_TooManyPinsForInterrupt;
                }
            }
            else
                errMsg = string.Format(Resource1.Err_PinCountOutOfRange, m_maxPinCount);


            if (!string.IsNullOrEmpty(errMsg))
            {
                e.Cancel = true;
                MessageBox.Show(errMsg, Resource1.Msg_InvalidNumberOfPins,
                    MessageBoxButtons.OK, MessageBoxIcon.Error, MessageBoxDefaultButton.Button1);
            }
            else
                m_port.PinCount = pinCount;

            base.OnValidating(e);
        }
    }

    [ExcludeFromCodeCoverage]
    [ToolStripItemDesignerAvailability(ToolStripItemDesignerAvailability.ToolStrip | ToolStripItemDesignerAvailability.StatusStrip)]
    public class ToolStripCheckBox : ToolStripControlHost
    {
        private CheckBox m_checkBox = null;
        
        public static implicit operator Control(ToolStripCheckBox tsbox)
        {
            return tsbox.m_checkBox;
        }

        public event EventHandler CheckedChanged
        {
            add { this.m_checkBox.CheckedChanged += value; }
            remove { this.m_checkBox.CheckedChanged -= value; }
        }
        public event EventHandler CheckStateChanged
        {
            add { this.m_checkBox.CheckStateChanged += value; }
            remove { this.m_checkBox.CheckStateChanged -= value; }
        }

        public override string Text
        {
            get { return this.m_checkBox.Text; }
            set
            {
                this.m_checkBox.Text = value;
                this.UpdateAutoSize();
            }
        }
        public bool Checked
        {
            get { return this.m_checkBox.Checked; }
            set { this.m_checkBox.Checked = value; }
        }
        public CheckState CheckState
        {
            get { return this.m_checkBox.CheckState; }
            set { this.m_checkBox.CheckState = value; }
        }

        public ToolStripCheckBox()
            : base(new CheckBox())
        {
            // Set up the FlowLayoutPanel.
            this.m_checkBox = (CheckBox)base.Control;
            this.m_checkBox.AutoSize = true;
        }

        protected void UpdateAutoSize()
        {
            if (!this.AutoSize) return;
            this.AutoSize = false;
            this.AutoSize = true;
        }
    }

    [ExcludeFromCodeCoverage]
    public class CyPerPinDataControl : UserControl
    {
        CyGeneralControl m_generalControl;
        CyInputControl m_inputControl;
        CyOutputControl m_outputControl;

        TabStripPage m_generalTab;
        TabStripPage m_inputTab;
        TabStripPage m_outputTab;

        TabStrip m_tabStrip;

        public CyPerPinDataControl(CyDeviceSupport deviceSupport, CyErrorManager errMgr, CyPinData cypin,
                                    CyPinPicture pinPicture, Action onSIOStateChanged)
        {
            Dock = DockStyle.Fill;

            m_tabStrip = new TabStrip();
            m_tabStrip.PageValidationEnabled = true;
            m_tabStrip.Renderer = new VisualStudio2005DocumentWindowTabStripRenderer();

            m_generalTab = new TabStripPage();
            m_generalTab.Text = "General";
            m_generalControl = new CyGeneralControl(deviceSupport, errMgr, cypin, pinPicture, onSIOStateChanged,
                (CyPinType pinType, IList<CyPinData.PerPin> pins) =>
                {
                    InputTabEnabled = pinType.IsOneOf(CyPinType.Bidirectional | CyPinType.Digital_In);
                    OutputTabEnabled = pinType.IsOneOf(CyPinType.Bidirectional | CyPinType.Digital_Out);
                    m_inputControl.UpdateData(pins); // Input sync may change when pin type changes
                },
                (IList<CyPinData.PerPin> pins) =>
                {
                    m_inputControl.UpdateData(pins);
                    m_outputControl.UpdateData(pins);
                });
            m_generalControl.Dock = DockStyle.Fill;
            m_generalTab.Controls.Add(m_generalControl);
            m_tabStrip.Pages.Add(m_generalTab);

            m_inputTab = new TabStripPage();
            m_inputTab.Text = "Input";
            m_inputControl = new CyInputControl(deviceSupport, errMgr, cypin, onSIOStateChanged);
            m_inputControl.Dock = DockStyle.Fill;
            m_inputTab.Controls.Add(m_inputControl);
            m_tabStrip.Pages.Add(m_inputTab);

            m_outputTab = new TabStripPage();
            m_outputTab.Text = "Output";
            m_outputControl = new CyOutputControl(deviceSupport, errMgr, cypin, onSIOStateChanged);
            m_outputControl.Dock = DockStyle.Fill;
            m_outputTab.Controls.Add(m_outputControl);
            m_tabStrip.Pages.Add(m_outputTab);

            m_tabStrip.Dock = DockStyle.Fill;
            Controls.Add(m_tabStrip);
        }

        public event TabStripPageEventHandler TabStripSelectionChanged 
        { 
            add { m_tabStrip.SelectionChanged += value; } 
            remove { m_tabStrip.SelectionChanged -= value; } 
        }

        public void UpdateData(IList<CyPinData.PerPin> selectedPins)
        {
            Debug.Assert(selectedPins.Count > 0);

            m_generalControl.UpdateData(selectedPins);
            m_inputControl.UpdateData(selectedPins);
            m_outputControl.UpdateData(selectedPins);
        }

        public bool InputTabEnabled
        {
            get { return m_inputTab.Enabled; }
            set
            {
                m_inputTab.Enabled = value;
                m_inputTab.ToolTipText = (value) ? string.Empty : Resource1.NoSelectedPinConfigured_input;
                // Some settings (e.g. CMOS) revert to default when Input isn't selected; make sure we're using
                // the real values now that we are actually an input
                if (value)
                    m_inputControl.UpdateData();
            }
        }

        public bool OutputTabEnabled
        {
            get { return m_outputTab.Enabled; }
            set
            {
                m_outputTab.Enabled = value;
                m_outputTab.ToolTipText = (value) ? string.Empty : Resource1.NoSelectedPinConfigured_output;
                // Some settings (e.g. CMOS) revert to default when Input isn't selected; make sure we're using
                // the real values now that we are actually an input
                if (value)
                    m_outputControl.UpdateData();
            }
        }

        public override Size GetPreferredSize(Size proposedSize)
        {
            // The controls we embed don't seem to report their preferred sizes particularly effectively,
            // so we will compute them directly here
            const int TAB_STRIP_HEIGHT = 20; // Tab strip is 20 pixels high at 120 DPI
            Control selectedControl = null;
            if (m_inputTab.IsSelected)
                selectedControl = m_inputControl;
            else if (m_outputTab.IsSelected)
                selectedControl = m_outputControl;
            else if (m_generalTab.IsSelected)
                selectedControl = m_generalControl;

            Debug.Assert(selectedControl != null, "Unknown control selected");

            Rectangle boundingBox = new Rectangle(0, 0, 0, 0);
            foreach (Control control in selectedControl.Controls)
            {
                boundingBox = Rectangle.Union(boundingBox, control.Bounds);
            }

            boundingBox.Height += TAB_STRIP_HEIGHT;
            return boundingBox.Size;
        }
    }
}
