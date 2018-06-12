using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Drawing;
using System.Data;
using System.Text;
using System.Windows.Forms;
using WaveDAC8_v2_10;

namespace WaveDAC8_v2_10
{
    partial class CyWaveDacTab
    {
        #region Component Designer generated code

        /// <summary> 
        /// Required method for Designer support - do not modify 
        /// the contents of this method with the code editor.
        /// </summary>
        private void InitializeComponent()
        {
            System.ComponentModel.ComponentResourceManager resources = new System.ComponentModel.ComponentResourceManager(typeof(CyWaveDacTab));
            this.m_cbRange = new System.Windows.Forms.ComboBox();
            this.m_lblRangeSelection = new System.Windows.Forms.Label();
            this.m_splitContainer = new System.Windows.Forms.SplitContainer();
            this.m_pnlHeader = new System.Windows.Forms.Panel();
            this.m_splitContainer.SuspendLayout();
            this.m_pnlHeader.SuspendLayout();
            this.SuspendLayout();
            // 
            // m_cbRange
            // 
            this.m_cbRange.DropDownStyle = System.Windows.Forms.ComboBoxStyle.DropDownList;
            resources.ApplyResources(this.m_cbRange, "m_cbRange");
            this.m_cbRange.FormattingEnabled = true;
            this.m_cbRange.Name = "m_cbRange";
            this.m_cbRange.SelectedIndexChanged += new System.EventHandler(this.cbRange_SelectedIndexChanged);
            // 
            // m_lblRangeSelection
            // 
            resources.ApplyResources(this.m_lblRangeSelection, "m_lblRangeSelection");
            this.m_lblRangeSelection.Name = "m_lblRangeSelection";
            // 
            // m_splitContainer
            // 
            resources.ApplyResources(this.m_splitContainer, "m_splitContainer");
            this.m_splitContainer.Name = "m_splitContainer";
            // 
            // m_pnlHeader
            // 
            this.m_pnlHeader.Controls.Add(this.m_lblRangeSelection);
            this.m_pnlHeader.Controls.Add(this.m_cbRange);
            resources.ApplyResources(this.m_pnlHeader, "m_pnlHeader");
            this.m_pnlHeader.Name = "m_pnlHeader";
            // 
            // CyWaveDacTab
            // 
            this.AutoScaleMode = System.Windows.Forms.AutoScaleMode.Inherit;
            resources.ApplyResources(this, "$this");
            this.Controls.Add(this.m_splitContainer);
            this.Controls.Add(this.m_pnlHeader);
            this.Name = "CyWaveDacTab";
            this.m_splitContainer.ResumeLayout(false);
            this.m_pnlHeader.ResumeLayout(false);
            this.m_pnlHeader.PerformLayout();
            this.ResumeLayout(false);

        }
        #endregion
        private ComboBox m_cbRange;
        private Label m_lblRangeSelection;
        private SplitContainer m_splitContainer;
        private Panel m_pnlHeader;
    }
}
