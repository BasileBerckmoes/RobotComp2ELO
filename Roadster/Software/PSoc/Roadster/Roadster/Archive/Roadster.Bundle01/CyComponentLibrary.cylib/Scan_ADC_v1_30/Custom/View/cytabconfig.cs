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
using CyDesigner.Extensions.Gde;
using System;
using System.Drawing;
using System.Text;
using System.Collections.Generic;

namespace Scan_ADC_v1_30
{
    public class CyConfigTab : CyTabControlWrapper
    {
        private System.Windows.Forms.TabControl m_tabConfig;
        private System.Windows.Forms.TabPage m_conversionTab;
        private CyConversionSubtab m_conversionControl;
        private CyFilterSubtab m_filterControl;
        private System.Windows.Forms.TabPage m_filterTab;
        
        private int m_configNumber = 0;

        #region CyTabControlWrapper Members

        public override string TabName
        {
            get
            {
                return this.TabDisplayName;
            }
        }
        #endregion

        public string TabDisplayName
        {
            get
            {
                return "Config" + m_configNumber.ToString();
            }
        }

        // Enable double buffering for form and form's controls.
        protected override System.Windows.Forms.CreateParams CreateParams
        {
            get
            {
                var cp = base.CreateParams;
                cp.ExStyle |= 0x02000000;
                return cp;
            }
        }

        #region Constructor(s)

        public CyConfigTab(CyParameters param)
            : this(param, 0)
        {
        }

        public CyConfigTab(CyParameters param, int configNumber)
            : base(param)
        {
            /* base class (CyTabControlWrapper) sets:
             * m_params = param;*/
            ConfigNumber = configNumber;
            InitializeComponent();

            this.m_conversionControl.SchedulerErrorsChange += UpdateTabErrors;
            this.m_conversionControl.SchedulerErrorsChange += this.m_filterControl.SchedulerUpdate;

            if (param.IsFilterAllowed)
            {
                this.m_filterControl.SchedulerErrorsChange += UpdateTabErrors;
                this.m_filterControl.SchedulerErrorsChange += this.m_conversionControl.SchedulerUpdate;
                this.m_filterControl.EnableRedraw = true;
            }
            else
            {
                this.m_filterControl.Visible = false;
                this.m_filterTab.Visible = false;
                this.m_tabConfig.Controls.Remove(this.m_filterTab);

                this.m_conversionControl.BackColor = Color.White;
                this.m_conversionControl.BorderStyle = System.Windows.Forms.BorderStyle.FixedSingle;

                this.m_tabConfig.Appearance = System.Windows.Forms.TabAppearance.FlatButtons;
                this.m_tabConfig.ItemSize = new System.Drawing.Size(0, 1);
                this.m_tabConfig.SizeMode = System.Windows.Forms.TabSizeMode.Fixed;
            }
        }

        #endregion

        private void InitializeComponent()
        {
            this.m_tabConfig = new System.Windows.Forms.TabControl();
            this.m_conversionTab = new System.Windows.Forms.TabPage();
            this.m_conversionControl = new CyConversionSubtab(base.m_params, m_configNumber);
            
            this.m_filterTab = new System.Windows.Forms.TabPage();
            this.m_filterControl = new CyFilterSubtab(base.m_params, m_configNumber);
            this.m_tabConfig.SuspendLayout();
            this.m_conversionTab.SuspendLayout();
            this.m_filterTab.SuspendLayout();
            this.SuspendLayout();
            // 
            // m_tabConfig
            // 
            this.m_tabConfig.Controls.Add(this.m_conversionTab);
            this.m_tabConfig.Controls.Add(this.m_filterTab);
            this.m_tabConfig.Location = new System.Drawing.Point(4, 4);
            this.m_tabConfig.Name = "m_tabConfig";
            this.m_tabConfig.SelectedIndex = 0;
            this.m_tabConfig.Size = new System.Drawing.Size(700, 900);
            this.m_tabConfig.TabIndex = 0;
            this.m_conversionControl.m_tlpSubTabConv.SizeChanged += m_conversionTab_SizeChanged;
            // 
            // m_conversionTab
            // 
            this.m_conversionTab.AutoScroll = true;
            this.m_conversionTab.Controls.Add(this.m_conversionControl);
            this.m_conversionTab.Location = new System.Drawing.Point(4, 22);
            this.m_conversionTab.Name = "m_conversionTab";
            this.m_conversionTab.Padding = new System.Windows.Forms.Padding(0);
            this.m_conversionTab.Size = new System.Drawing.Size(700, 900);
            this.m_conversionTab.TabIndex = 0;
            this.m_conversionTab.Text = "Scan";
            this.m_conversionTab.UseVisualStyleBackColor = true;
            // 
            // m_conversionControl
            // 
            this.m_conversionControl.AutoScroll = true;
            this.m_conversionControl.AutoSize = true;
            this.m_conversionControl.AutoSizeMode = System.Windows.Forms.AutoSizeMode.GrowAndShrink;
            this.m_conversionControl.Dock = System.Windows.Forms.DockStyle.Fill;
            this.m_conversionControl.Location = new System.Drawing.Point(3, 3);
            this.m_conversionControl.Name = "m_conversionControl";
            this.m_conversionControl.Size = new System.Drawing.Size(300, 900);
            this.m_conversionControl.TabIndex = 0;
            // 
            // m_filterTab
            // 
            this.m_filterTab.AutoSize = true;
            this.m_filterTab.AutoScroll = true;
            this.m_filterTab.Controls.Add(this.m_filterControl);
            this.m_filterTab.Location = new System.Drawing.Point(4, 22);
            this.m_filterTab.Name = "m_filterTab";
            this.m_filterTab.Padding = new System.Windows.Forms.Padding(0);
            this.m_filterTab.Size = new System.Drawing.Size(630, 516);
            this.m_filterTab.TabIndex = 1;
            this.m_filterTab.Text = "Filter";
            this.m_filterTab.UseVisualStyleBackColor = true;
            // 
            // m_filterControl
            // 
            this.m_filterControl.AutoSize = true;
            this.m_filterControl.AutoScroll = true;
            this.m_filterControl.Dock = System.Windows.Forms.DockStyle.Fill;
            this.m_filterControl.Location = new System.Drawing.Point(3, 3);
            this.m_filterControl.Name = "m_filterControl";
            this.m_filterControl.Size = new System.Drawing.Size(624, 510);
            this.m_filterControl.TabIndex = 0;
            // 
            // CyConfigTab
            // 
            this.AutoSize = true;
            this.AutoSizeMode = System.Windows.Forms.AutoSizeMode.GrowAndShrink;
            this.Anchor = System.Windows.Forms.AnchorStyles.Bottom |
                System.Windows.Forms.AnchorStyles.Top |
                System.Windows.Forms.AnchorStyles.Left |
                System.Windows.Forms.AnchorStyles.Right;
            this.AutoScroll = true;
            this.Controls.Add(this.m_tabConfig);
            this.Name = "CyConfigTab";
            this.Size = new System.Drawing.Size(700, 900);
            this.m_tabConfig.ResumeLayout(false);
            this.m_conversionTab.ResumeLayout(false);
            this.m_conversionTab.PerformLayout();
            this.m_filterTab.ResumeLayout(false);
            this.ResumeLayout(false);
            m_conversionTab_SizeChanged(null, EventArgs.Empty);
        }

        void m_conversionTab_SizeChanged(object sender, EventArgs e)
        {
            var width = m_conversionControl.m_tlpSubTabConv.Size.Width
                + m_tabConfig.Margin.Horizontal
                + m_conversionTab.Padding.Horizontal
                + m_conversionTab.Margin.Horizontal
                + m_conversionControl.Padding.Horizontal
                + m_conversionControl.Margin.Horizontal;
            var height = m_conversionControl.m_tlpSubTabConv.Size.Height
                + m_tabConfig.Margin.Vertical
                + m_conversionTab.Padding.Vertical
                + m_conversionTab.Margin.Vertical
                + m_conversionControl.Padding.Vertical
                + m_conversionControl.Margin.Vertical
                + (m_tabConfig.ItemSize.Height > 0 ? m_tabConfig.ItemSize.Height : 22);
            m_tabConfig.Size = new System.Drawing.Size(width, height);
        }

        public void UpdateTabErrors(List<CyDRCInfo_v1> schedErrList)
        {
            if (schedErrList != null && schedErrList.Count != 0)
            {
                this.m_errorProvider.SetIconPadding(m_tabConfig, -1 * (2 * m_tabConfig.ItemSize.Width + 19));

                this.m_errorProvider.SetIconAlignment(m_tabConfig, System.Windows.Forms.ErrorIconAlignment.TopLeft);
                StringBuilder guiErrMsg = new StringBuilder();
                foreach (CyDRCInfo_v1 schedDrc in schedErrList)
                {
                    guiErrMsg.Append(schedDrc.Message);
                    guiErrMsg.Append("\n");
                }
                this.m_errorProvider.SetError(m_tabConfig, guiErrMsg.ToString());
            }
            else
            {
                this.m_errorProvider.SetError(m_tabConfig, String.Empty);
            }
        }

        public void UpdateUI()
        {
            m_conversionControl.UpdateUI();
            m_filterControl.UpdateUI();
            m_conversionTab_SizeChanged(null, EventArgs.Empty);
            UpdateTabErrors(new List<CyDRCInfo_v1>());
        }

        public int ConfigNumber
        {
            get{ return m_configNumber;}
            set{m_configNumber = value;}
        }
    }
}

//[] END OF FILE
