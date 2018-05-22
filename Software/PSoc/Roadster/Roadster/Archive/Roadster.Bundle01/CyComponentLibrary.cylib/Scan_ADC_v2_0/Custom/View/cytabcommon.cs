/* ========================================
 *
 * Copyright YOUR COMPANY, THE YEAR
 * All Rights Reserved
 * UNPUBLISHED, LICENSED SOFTWARE.
 *
 * CONFIDENTIAL AND PROPRIETARY INFORMATION
 * WHICH IS THE PROPERTY OF your company.
 *
 * ========================================
*/
using System;
using System.Collections.Generic;
using System.Text;
using CyDesigner.Extensions.Gde;
using System.ComponentModel;
using CyDesigner.Extensions.Common;
using System.Windows.Forms;
using System.Drawing;
using System.Xml.Serialization;
using System.Xml;
using System.IO;
using System.Diagnostics;


namespace Scan_ADC_v2_0
{
    public class CyCommonTab : CyTabControlWrapper
    {
        private System.Windows.Forms.NumericUpDown m_nudNumberOfConfigs;
        private System.Windows.Forms.CheckBox m_cbExternalClk;
        private ToolTip m_commonToolTip;
        private IContainer components;
        private System.Windows.Forms.Label m_lNumberOfConfigs;
        private TableLayoutPanel tableLayoutPanel1;
        private NumericUpDown m_nudConfigSpacing;
        private Label m_lConfigSpacing;
        
        #region CyTabControlWrapper Members
        public override string TabName
        {
            get
            {
                return global::Scan_ADC_v2_0.View.cytooltips.commonTabName;
            }
        }
        #endregion

        #region Constructor(s)
        public CyCommonTab(CyParameters param)
            : base(param) {
                InitializeComponent();
                SetComponentsStates();
                UpdateUI();
            }
        #endregion

        private void InitializeComponent()
        {
            this.components = new System.ComponentModel.Container();
            this.m_lNumberOfConfigs = new System.Windows.Forms.Label();
            this.m_nudNumberOfConfigs = new System.Windows.Forms.NumericUpDown();
            this.m_cbExternalClk = new System.Windows.Forms.CheckBox();
            this.m_commonToolTip = new System.Windows.Forms.ToolTip(this.components);
            this.tableLayoutPanel1 = new System.Windows.Forms.TableLayoutPanel();
            this.m_lConfigSpacing = new System.Windows.Forms.Label();
            this.m_nudConfigSpacing = new System.Windows.Forms.NumericUpDown();
            ((System.ComponentModel.ISupportInitialize)(this.m_nudNumberOfConfigs)).BeginInit();
            this.tableLayoutPanel1.SuspendLayout();
            ((System.ComponentModel.ISupportInitialize)(this.m_nudConfigSpacing)).BeginInit();
            this.SuspendLayout();
            // 
            // m_lNumberOfConfigs
            // 
            this.m_lNumberOfConfigs.Anchor = System.Windows.Forms.AnchorStyles.Left;
            this.m_lNumberOfConfigs.AutoSize = true;
            this.m_lNumberOfConfigs.Location = new System.Drawing.Point(3, 6);
            this.m_lNumberOfConfigs.Name = "m_lNumberOfConfigs";
            this.m_lNumberOfConfigs.Size = new System.Drawing.Size(96, 13);
            this.m_lNumberOfConfigs.TabIndex = 0;
            this.m_lNumberOfConfigs.Text = "Number of configs:";
            this.m_commonToolTip.SetToolTip(this.m_lNumberOfConfigs, "Set the number of distinct scan configurations. (From 1 to 4)");
            // 
            // m_nudNumberOfConfigs
            // 
            this.m_nudNumberOfConfigs.Anchor = System.Windows.Forms.AnchorStyles.Left;
            this.m_nudNumberOfConfigs.Location = new System.Drawing.Point(105, 3);
            this.m_nudNumberOfConfigs.Name = "m_nudNumberOfConfigs";
            this.m_nudNumberOfConfigs.Size = new System.Drawing.Size(107, 20);
            this.m_nudNumberOfConfigs.TabIndex = 1;
            this.m_commonToolTip.SetToolTip(this.m_nudNumberOfConfigs, "Set the number of distinct scan configurations. (From 1 to 4)");
            this.m_nudNumberOfConfigs.TextChanged += new System.EventHandler(this.nud_TextChanged);
            // 
            // m_cbExternalClk
            // 
            this.m_cbExternalClk.Anchor = System.Windows.Forms.AnchorStyles.Left;
            this.m_cbExternalClk.AutoSize = true;
            this.tableLayoutPanel1.SetColumnSpan(this.m_cbExternalClk, 2);
            this.m_cbExternalClk.Location = new System.Drawing.Point(3, 29);
            this.m_cbExternalClk.Name = "m_cbExternalClk";
            this.m_cbExternalClk.Size = new System.Drawing.Size(185, 17);
            this.m_cbExternalClk.TabIndex = 3;
            this.m_cbExternalClk.Text = "Show analog clock (aclk) terminal";
            this.m_commonToolTip.SetToolTip(this.m_cbExternalClk, "Select whether to use an external clock.");
            this.m_cbExternalClk.UseVisualStyleBackColor = true;
            this.m_cbExternalClk.CheckedChanged += new System.EventHandler(this.cb_CheckedChanged);
            // 
            // tableLayoutPanel1
            // 
            this.tableLayoutPanel1.AutoSize = true;
            this.tableLayoutPanel1.AutoSizeMode = System.Windows.Forms.AutoSizeMode.GrowAndShrink;
            this.tableLayoutPanel1.ColumnCount = 4;
            this.tableLayoutPanel1.ColumnStyles.Add(new System.Windows.Forms.ColumnStyle());
            this.tableLayoutPanel1.ColumnStyles.Add(new System.Windows.Forms.ColumnStyle());
            this.tableLayoutPanel1.ColumnStyles.Add(new System.Windows.Forms.ColumnStyle());
            this.tableLayoutPanel1.ColumnStyles.Add(new System.Windows.Forms.ColumnStyle());
            this.tableLayoutPanel1.Controls.Add(this.m_lNumberOfConfigs, 0, 0);
            this.tableLayoutPanel1.Controls.Add(this.m_nudNumberOfConfigs, 1, 0);
            this.tableLayoutPanel1.Controls.Add(this.m_cbExternalClk, 0, 1);
            this.tableLayoutPanel1.Controls.Add(this.m_lConfigSpacing, 2, 0);
            this.tableLayoutPanel1.Controls.Add(this.m_nudConfigSpacing, 3, 0);
            this.tableLayoutPanel1.Dock = System.Windows.Forms.DockStyle.Top;
            this.tableLayoutPanel1.Location = new System.Drawing.Point(0, 0);
            this.tableLayoutPanel1.Name = "tableLayoutPanel1";
            this.tableLayoutPanel1.RowCount = 3;
            this.tableLayoutPanel1.RowStyles.Add(new System.Windows.Forms.RowStyle());
            this.tableLayoutPanel1.RowStyles.Add(new System.Windows.Forms.RowStyle());
            this.tableLayoutPanel1.RowStyles.Add(new System.Windows.Forms.RowStyle());
            this.tableLayoutPanel1.Size = new System.Drawing.Size(669, 49);
            this.tableLayoutPanel1.TabIndex = 3;
            // 
            // m_lConfigSpacing
            // 
            this.m_lConfigSpacing.Anchor = System.Windows.Forms.AnchorStyles.Left;
            this.m_lConfigSpacing.AutoSize = true;
            this.m_lConfigSpacing.Location = new System.Drawing.Point(218, 6);
            this.m_lConfigSpacing.Name = "m_lConfigSpacing";
            this.m_lConfigSpacing.Size = new System.Drawing.Size(208, 13);
            this.m_lConfigSpacing.TabIndex = 5;
            this.m_lConfigSpacing.Text = "Space between config symbols (grid units):";
            this.m_lConfigSpacing.Visible = false;
            // 
            // m_nudConfigSpacing
            // 
            this.m_nudConfigSpacing.Anchor = System.Windows.Forms.AnchorStyles.Left;
            this.m_nudConfigSpacing.Location = new System.Drawing.Point(432, 3);
            this.m_nudConfigSpacing.Maximum = new decimal(new int[] {
            45,
            0,
            0,
            0});
            this.m_nudConfigSpacing.Minimum = new decimal(new int[] {
            10,
            0,
            0,
            0});
            this.m_nudConfigSpacing.Name = "m_nudConfigSpacing";
            this.m_nudConfigSpacing.Size = new System.Drawing.Size(71, 20);
            this.m_nudConfigSpacing.TabIndex = 2;
            this.m_nudConfigSpacing.Value = new decimal(new int[] {
            15,
            0,
            0,
            0});
            this.m_nudConfigSpacing.Visible = false;
            this.m_nudConfigSpacing.TextChanged += new System.EventHandler(this.nud_TextChanged);
            // 
            // CyCommonTab
            // 
            this.Controls.Add(this.tableLayoutPanel1);
            this.Name = "CyCommonTab";
            this.Size = new System.Drawing.Size(669, 180);
            ((System.ComponentModel.ISupportInitialize)(this.m_nudNumberOfConfigs)).EndInit();
            this.tableLayoutPanel1.ResumeLayout(false);
            this.tableLayoutPanel1.PerformLayout();
            ((System.ComponentModel.ISupportInitialize)(this.m_nudConfigSpacing)).EndInit();
            this.ResumeLayout(false);
            this.PerformLayout();

        }

        public void SetComponentsStates()
        {
            m_nudNumberOfConfigs.Minimum = CyParamRanges.NUM_CONFIG_MIN;
            m_nudNumberOfConfigs.Maximum = CyParamRanges.NUM_CONFIG_MAX;
        }


        private void SetToolTips()
        {
            this.m_commonToolTip.SetToolTip(this.m_lNumberOfConfigs, Scan_ADC_v2_0.View.cytooltips.numberOfConfigsToolTip);
            this.m_commonToolTip.SetToolTip(this.m_nudNumberOfConfigs, Scan_ADC_v2_0.View.cytooltips.numberOfConfigsToolTip);
            this.m_commonToolTip.SetToolTip(this.m_cbExternalClk, Scan_ADC_v2_0.View.cytooltips.clockToolTip);

        }

        public void UpdateUI()
        {
            m_nudNumberOfConfigs.Value = (decimal)m_params.NumberOfConfigs;
            m_nudConfigSpacing.Value = (decimal)m_params.Test_ConfigSpacing;
            m_cbExternalClk.Checked = m_params.ExternalClk;
            SetToolTips();
        }

        private void nud_ValueChanged(object sender, EventArgs e)
        {
            if (sender == m_nudNumberOfConfigs)
            {
                m_params.NumberOfConfigs = (int)m_nudNumberOfConfigs.Value;
                m_params.ExternalSoc = CyModelUtils.AnyConfigHasUseSoc(m_params);
                SetConfigSpacingState();
            }
            else if (sender == m_nudConfigSpacing)
            {
                m_params.Test_ConfigSpacing = (int)m_nudConfigSpacing.Value;
            }
            else
            {

            }
        }

        private void nud_TextChanged(object sender, EventArgs e)
        {
            // Normally the NumericUpDown doesn't send ValueChanged until it is unfocused.
            // To update dependent controls sooner, use TextChanged instead.
            NumericUpDown control = (NumericUpDown)sender;
            decimal? newValueNullable = CyConversionSubtab.GetNumUpDownValue(control);
            if (!newValueNullable.HasValue)
                return;
            decimal newValue = newValueNullable.Value;

            if (sender == m_nudNumberOfConfigs)
            {
                m_params.NumberOfConfigs = (int)m_nudNumberOfConfigs.Value;
                m_params.ExternalSoc = CyModelUtils.AnyConfigHasUseSoc(m_params);
                SetConfigSpacingState();
            }
            else if (sender == m_nudConfigSpacing)
            {
                m_params.Test_ConfigSpacing = (int)m_nudConfigSpacing.Value;
            }
        }

        private void cb_CheckedChanged(object sender, EventArgs e)
        {
            if (sender == m_cbExternalClk)
            {
                m_params.ExternalClk = m_cbExternalClk.Checked;
                m_params.OnSideEffectChange();
            }
            else
            {
            }
        }

        private void SetConfigSpacingState()
        {
            if (m_nudNumberOfConfigs.Value > 1)
            {
                m_lConfigSpacing.Visible = true;
                m_nudConfigSpacing.Visible = true;
            }
            else
            {
                m_lConfigSpacing.Visible = false;
                m_nudConfigSpacing.Visible = false;
            }
        }
    }

}

//[] END OF FILE
