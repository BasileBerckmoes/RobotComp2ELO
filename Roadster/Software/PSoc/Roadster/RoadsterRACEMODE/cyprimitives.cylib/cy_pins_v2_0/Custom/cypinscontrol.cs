/*******************************************************************************
* Copyright 2008-2013, Cypress Semiconductor Corporation.  All rights reserved.
* You may use this file only in accordance with the license, terms, conditions, 
* disclaimers, and limitations in the end user license agreement accompanying 
* the software package with which this file was provided.
********************************************************************************/

using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Drawing;
using System.Windows.Forms;
using System.Diagnostics;

using CyDesigner.Common.Base.Controls;
using CyDesigner.Extensions.Common;
using CyDesigner.Extensions.Gde;

using ActiproSoftware.UIStudio.TabStrip;

namespace Cypress.Comps.PinsAndPorts.cy_pins_v2_0
{
    /// <summary>
    /// Contains a SplitContainer with a tree on the left and params on the right.
    /// </summary>
    public partial class CyPinsControl : UserControl, ICyParamEditingControl
    {
        private readonly CyPinData m_port;
        private readonly CyErrorManager m_errMgr;
        private readonly int PinImageIndex;
        private readonly int SIOPinImageIndex;

        private CyNumPinsToolStripTextBox m_numPinsTextBox;
        private ToolStripButton m_moveUpButton;
        private ToolStripButton m_moveDownButton;
        private ToolStripButton m_deleteButton;
        private ToolStripButton m_renameButton;
        private ToolStripButton m_groupSIOButton;
        private ToolStripButton m_ungroupSIOButton;

        private const int AllPinsTag = -2;
        private const int SIOPairTag = -3;
        private CyPerPinDataControl m_perPinDataControl;

        public CyPinsControl(CyDeviceSupport deviceSupport, CyErrorManager errMgr, CyPinData pins)
        {
            InitializeComponent();

            m_port = pins;
            m_errMgr = errMgr;
            Dock = DockStyle.Fill;

            m_splitContainer.FixedPanel = FixedPanel.Panel1;

            m_treeView.CheckBoxes = CyTreeView.CheckBoxDisplay.SHOW_NONE;
            m_treeView.ShowRootLines = false;
            m_treeView.HideSelection = false;
            m_treeView.ShowNodeToolTips = true;
            m_treeView.FocusWhenSelectedNodeChanged = false;
            m_treeView.ImageList = new CyTableViewBase.CyImageList();
            PinImageIndex = m_treeView.ImageList.AddImage(Resource1.PinImage);
            SIOPinImageIndex = m_treeView.ImageList.AddImage(Resource1.SIOPinImage);

            m_toolStrip.CanOverflow = true;
            m_toolStrip.GripStyle = ToolStripGripStyle.Hidden;
            m_toolStrip.RenderMode = ToolStripRenderMode.System;
            m_toolStrip.ShowItemToolTips = true;

            ToolStripLabel numPinsLabel = new ToolStripLabel("Number of Pins:");
            m_toolStrip.Items.Add(numPinsLabel);

            m_numPinsTextBox = new CyNumPinsToolStripTextBox(pins);
            m_toolStrip.Items.Add(m_numPinsTextBox);

            m_toolStrip.Items.Add(new ToolStripSeparator());

            m_deleteButton = 
                new ToolStripButton("Delete Selected Pin/s (Delete)", Resource1.DeleteImage, DeletePinClicked);
            m_deleteButton.DisplayStyle = ToolStripItemDisplayStyle.Image;
            m_toolStrip.Items.Add(m_deleteButton);

            m_renameButton = 
                new ToolStripButton("Change Selected Pin's Alias... (F2)", Resource1.PinAliasImage, RenamePinClicked);
            m_renameButton.DisplayStyle = ToolStripItemDisplayStyle.Image;
            m_toolStrip.Items.Add(m_renameButton);

            m_moveUpButton = new ToolStripButton("Move Selected Pin/s Up", Resource1.MoveUpImage, MovePinUpClicked);
            m_moveUpButton.DisplayStyle = ToolStripItemDisplayStyle.Image;
            m_toolStrip.Items.Add(m_moveUpButton);

            m_moveDownButton = 
                new ToolStripButton("Move Selected Pin/s Down", Resource1.MoveDownImage, MovePinDownClicked);
            m_moveDownButton.DisplayStyle = ToolStripItemDisplayStyle.Image;
            m_toolStrip.Items.Add(m_moveDownButton);

            m_toolStrip.Items.Add(new ToolStripSeparator());

            m_groupSIOButton = new ToolStripButton("Pair Selected SIOs", Resource1.PairSIOsImage, PairSIOsClicked);
            m_groupSIOButton.DisplayStyle = ToolStripItemDisplayStyle.Image;
            m_toolStrip.Items.Add(m_groupSIOButton);

            m_ungroupSIOButton = 
                new ToolStripButton("Un-pair Selected SIOs", Resource1.UnpairSIOsImage, UnpairSIOsClicked);
            m_ungroupSIOButton.DisplayStyle = ToolStripItemDisplayStyle.Image;
            m_toolStrip.Items.Add(m_ungroupSIOButton);

            m_toolStrip.Items.Add(new ToolStripSeparator());

            m_perPinDataControl = new CyPerPinDataControl(deviceSupport, errMgr, pins, PinSIOStateChanged);
            m_splitContainer.Panel2.Controls.Add(m_perPinDataControl);

            RebuildTree();
            UpdateData();
            UpdatePerPinDataDisplayed();

            m_treeView.BeforeCollapse += m_treeView_BeforeCollapse;
            m_treeView.AfterMultiSelect += m_treeView_AfterMultiSelect;
            m_treeView.NodeMouseDoubleClick += m_treeView_NodeMouseDoubleClick;
            m_numPinsTextBox.Validated += m_numPinsTextBox_Validated;
        }

        private void PerformDispose()
        {
            m_treeView.BeforeCollapse -= m_treeView_BeforeCollapse;
            m_treeView.AfterMultiSelect -= m_treeView_AfterMultiSelect;
            m_treeView.NodeMouseDoubleClick -= m_treeView_NodeMouseDoubleClick;
            m_numPinsTextBox.Validated -= m_numPinsTextBox_Validated;
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

                if (m_port[i].IsSIO())
                {
                    if (m_port[i].SIOPairID >= 0)
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
                    else
                    {
                        leafNode.ImageIndex = SIOPinImageIndex;
                        rootNode.Nodes.Add(leafNode);
                    }
                }
                else
                {
                    leafNode.ImageIndex = PinImageIndex;
                    rootNode.Nodes.Add(leafNode);
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
                    else
                    {
                        if (!indexes.Contains(tagInt))
                            indexes.Add(tagInt);
                    }
                }
            }

            return indexes;
        }

        private int GetNumLeafNodes()
        {
            int cnt = 0;
            foreach (CyTreeNode node in m_treeView.GetAllNodesInTree())
            {
                if (node.Nodes.Count == 0)
                    cnt++;
            }
            return cnt;
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
                    {
                        if (index == GetPinIndex(node))
                        {
                            nodes.Add(node);
                        }
                    }
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
            foreach (CyTreeNode node in m_treeView.GetAllNodesInTree())
            {
                int nodesPinIndex = GetPinIndex(node);
                if (nodesPinIndex == index)
                   return node;
            }

            return null;
        }

        private IList<CyPinData.PerPin> GetSelectedPins(IList<int> pinIndexes)
        {
            CyPinData.PerPin[] pins = new CyPinData.PerPin[pinIndexes.Count];
            for (int i = 0; i < pinIndexes.Count; i++)
                pins[i] = m_port[pinIndexes[i]];
            return pins;
        }

        #region Per Pin Data

        private void UpdatePerPinDataDisplayed()
        {
            List<int> selectedPinIndexes = GetPinIndexes(m_treeView.SelectedNodes);
            IList<CyPinData.PerPin> selectedPins = GetSelectedPins(selectedPinIndexes);
            m_perPinDataControl.UpdateData(selectedPins);

            m_perPinDataControl.InputTabEnabled = InputUsed(selectedPins);
            m_perPinDataControl.OutputTabEnabled = OutputUsed(selectedPins);
        }

        private static bool InputUsed(ICollection<CyPinData.PerPin> selectedPins)
        {
            bool used = false;
            foreach (CyPinData.PerPin pin in selectedPins)
                used |= ((pin.Type & (CyPinType.BIDIRECTIONAL | CyPinType.DIGITAL_IN)) > 0);
            return used;
        }

        private static bool OutputUsed(ICollection<CyPinData.PerPin> selectedPins)
        {
            bool used = false;
            foreach (CyPinData.PerPin pin in selectedPins)
                used |= ((pin.Type & (CyPinType.BIDIRECTIONAL | CyPinType.DIGITAL_OUT)) > 0);
            return used;
        }

        #endregion

        #region ToolStrip Handlers

        private void UpdateToolStripItemsEnabled()
        {
            int numLeafNodes = GetNumLeafNodes();

            m_deleteButton.Enabled = false;
            m_renameButton.Enabled = false;
            m_moveUpButton.Enabled = false;
            m_moveDownButton.Enabled = false;
            m_groupSIOButton.Enabled = false;
            m_ungroupSIOButton.Enabled = false;

            m_groupSIOButton.ToolTipText = "Pair SIOs cannot be performed. SIOs can only be paired if " +
                "they are adjacent to each other and not already in a pair.";
            m_deleteButton.ToolTipText = String.Empty;

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
                    if ((index2 - index1) == 1 && pin1.IsSIO() && pin2.IsSIO())
                    {
                        if (pin1.SIOPairID == 0 && pin2.SIOPairID == 1)
                            m_ungroupSIOButton.Enabled = true;
                        else if (pin1.SIOPairID == -1 && pin2.SIOPairID == -1)
                        {
                            m_groupSIOButton.Enabled = true;
                            m_groupSIOButton.ToolTipText = String.Empty;
                        }
                    }
                }

                m_deleteButton.Enabled = numLeafNodes - selectedPinIndexes.Count > 0;
                m_deleteButton.ToolTipText = (m_deleteButton.Enabled) 
                    ? String.Empty 
                    : "Delete Selected Pin/s cannot be performed. Cannot have less than one pin remaining.";

                //otherwise already as low as it can go
                m_moveDownButton.Enabled = (selectedPinIndexes.Contains(numLeafNodes - 1) == false);

                //otherwise already as high as it can go
                m_moveUpButton.Enabled = (selectedPinIndexes.Contains(0) == false);
            }
        }

        protected override bool ProcessCmdKey(ref Message msg, Keys keyData)
        {
            switch (keyData)
            {
                case Keys.F2:
                    m_renameButton.PerformClick();
                    break;

                case Keys.Delete:
                    if(m_treeView.ContainsFocus)
                        m_deleteButton.PerformClick();
                    break;

                case Keys.Control | Keys.A:
                    m_treeView.SelectAll();
                    break;
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

        void PairSIOsClicked(object sender, EventArgs e)
        {
            SetSioGroup(true);
        }

        void UnpairSIOsClicked(object sender, EventArgs e)
        {
            SetSioGroup(false);
        }

        void PinSIOStateChanged()
        {
            RebuildTree();
        }

        void SetSioGroup(bool pair)
        {
            List<int> selectedPinIndexes = GetPinIndexes(m_treeView.SelectedNodes);
            selectedPinIndexes.Sort(); // GetPinIndexes returns indexes in the order they were selected
            Debug.Assert(selectedPinIndexes.Count == 2);

            m_port[selectedPinIndexes[0]].SIOPairID = pair ? 0 : -1;
            m_port[selectedPinIndexes[1]].SIOPairID = pair ? 1 : -1;

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
            foreach (string errMsg in m_errMgr.GetErrors(CyTypeControl.OwnedSettings))
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

    public class CyNumPinsToolStripTextBox : ToolStripTextBox
    {
        CyPinData m_port;

        public CyNumPinsToolStripTextBox(CyPinData port)
        {
            m_port = port;
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
                if (pinCount > 64 || pinCount < 1)
                    errMsg = "NumPins Validation Failed. The width must be between 1 and 64.";
                else if (pinCount > 8)
                {
                    if (pinCount > 8 && !m_port.MappingSpanning)
                    {
                        errMsg = "NumPins Validation Failed. The number of pins must be less than or equal to " +
                            "8 if spanning is not allowed.";
                    }
                    else
                    {
                        for (int i = 0; i < Math.Min((byte)8, m_port.PinCount); i++)
                        {
                            if (m_port[i].InputInterrupt != CyInputInterruptTrigger.NONE)
                                errMsg = "NumPins Validation Failed. The number of pins must be less than " +
                                    "or equal to 8 when interrupts are used inorder for them all to fit " +
                                    "within a single physical port.";
                        }
                    }
                }
            }
            else
                errMsg = "NumPins Validation Failed. The width must be a number between 1 and 64.";


            if (!string.IsNullOrEmpty(errMsg))
            {
                e.Cancel = true;
                MessageBox.Show(errMsg, "Invalid Number of Pins", MessageBoxButtons.OK, MessageBoxIcon.Error,
                    MessageBoxDefaultButton.Button1);
            }
            else
                m_port.PinCount = pinCount;

            base.OnValidating(e);
        }
    }

    public class CyPerPinDataControl : UserControl
    {
        CyErrorManager m_errMgr;
        public delegate void SIOStateChangedHandler();

        CyTypeControl m_typeControl;
        CyGeneralControl m_generalControl;
        CyInputControl m_inputControl;
        CyOutputControl m_outputControl;

        TabStripPage m_typeTab;
        TabStripPage m_generalTab;
        TabStripPage m_inputTab;
        TabStripPage m_outputTab;

        public CyPerPinDataControl(CyDeviceSupport deviceSupport, CyErrorManager errMgr, CyPinData pins,
                                    SIOStateChangedHandler onSIOStateChanged)
        {
            Dock = DockStyle.Fill;

            m_errMgr = errMgr;

            TabStrip tabControl = new TabStrip();
            tabControl.PageValidationEnabled = true;
            tabControl.Renderer = new VisualStudio2005DocumentWindowTabStripRenderer();

            m_typeTab = new TabStripPage();
            m_typeTab.Text = "Type";
            m_typeControl = new CyTypeControl(deviceSupport, errMgr, pins, PinTypeChanged);
            m_typeControl.Dock = DockStyle.Fill;
            m_typeTab.Controls.Add(m_typeControl);
            tabControl.Pages.Add(m_typeTab);

            m_generalTab = new TabStripPage();
            m_generalTab.Text = "General";
            m_generalControl = new CyGeneralControl(deviceSupport, errMgr);
            m_generalControl.Dock = DockStyle.Fill;
            m_generalTab.Controls.Add(m_generalControl);
            tabControl.Pages.Add(m_generalTab);

            m_inputTab = new TabStripPage();
            m_inputTab.Text = "Input";
            m_inputControl = new CyInputControl(deviceSupport, errMgr, pins, onSIOStateChanged);
            m_inputControl.Dock = DockStyle.Fill;
            m_inputTab.Controls.Add(m_inputControl);
            tabControl.Pages.Add(m_inputTab);

            m_outputTab = new TabStripPage();
            m_outputTab.Text = "Output";
            m_outputControl = new CyOutputControl(deviceSupport, errMgr, pins, onSIOStateChanged);
            m_outputControl.Dock = DockStyle.Fill;
            m_outputTab.Controls.Add(m_outputControl);
            tabControl.Pages.Add(m_outputTab);

            tabControl.Dock = DockStyle.Fill;
            Controls.Add(tabControl);
        }

        private void PinTypeChanged(CyPinType pinType, IList<CyPinData.PerPin> pins)
        {
            InputTabEnabled = ((pinType & (CyPinType.BIDIRECTIONAL | CyPinType.DIGITAL_IN)) > 0);
            OutputTabEnabled = ((pinType & (CyPinType.BIDIRECTIONAL | CyPinType.DIGITAL_OUT)) > 0);
            m_generalControl.UpdateData(pins);
        }

        public void UpdateData(IList<CyPinData.PerPin> selectedPins)
        {
            Debug.Assert(selectedPins.Count > 0);

            m_typeControl.UpdateData(selectedPins);
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
                m_inputTab.ToolTipText = (value) 
                    ? string.Empty 
                    : "None of the selected pins have their PinType configured to use input settings.";
            }
        }

        public bool OutputTabEnabled
        {
            get { return m_outputTab.Enabled; }
            set
            {
                m_outputTab.Enabled = value;
                m_outputTab.ToolTipText = (value) 
                    ? string.Empty 
                    : "None of the selected pins have their PinType configured to use output settings.";
            }
        }

        void UpdateTypeTabErrorIcon()
        {
            m_typeTab.ContextImage = m_errMgr.HasError(CyTypeControl.OwnedSettings)
                ? Resource1.ErrorImage
                : null;
        }

        void UpdateGeneralTabErrorIcon()
        {
            m_generalTab.ContextImage = m_errMgr.HasError(CyGeneralControl.OwnedSettings)
                ? Resource1.ErrorImage
                : null;
        }

        void UpdateInputTabErrorIcon()
        {
            m_inputTab.ContextImage = m_errMgr.HasError(CyInputControl.OwnedSettings)
                ? Resource1.ErrorImage
                : null;
        }

        void UpdateOutputTabErrorIcon()
        {
            m_outputTab.ContextImage = m_errMgr.HasError(CyOutputControl.OwnedSettings)
                ? Resource1.ErrorImage
                : null;
        }
    }
}
