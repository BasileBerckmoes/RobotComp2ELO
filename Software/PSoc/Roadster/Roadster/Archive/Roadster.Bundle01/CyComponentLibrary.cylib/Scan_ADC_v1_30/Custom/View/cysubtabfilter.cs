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
using System.Windows.Forms;
using System.Collections.Generic;
using CyDesigner.Extensions.Gde;

namespace Scan_ADC_v1_30
{
    public class CyFilterSubtab : CyTabControlWrapper
    {
        public System.Windows.Forms.ComboBox m_cmbFilterType;
        public System.Windows.Forms.Label m_lFilterType;
        public System.Windows.Forms.Label m_l3dB_or_centerFreq;
        public System.Windows.Forms.Label m_lNotch_or_bandwidthFreq;
        public System.Windows.Forms.NumericUpDown m_nud3dB_or_centerFreq;
        public System.Windows.Forms.NumericUpDown m_nudNotch_or_bandwidthFreq;
        private System.Windows.Forms.ToolTip m_filterToolTip;
        private System.ComponentModel.IContainer components;
        private System.Windows.Forms.Panel m_pnlControls;
        private System.Windows.Forms.Panel m_pnlGraph;
        private CyBodeControl m_bodeControl;
        public Label m_lSampleFreq;
        private Label m_lSampleFreqValue;

        public int m_configNumber;
        private bool m_blockParamUpdate;
        private TableLayoutPanel m_tblControls;

        private decimal m_hp_cutoff =  CyParamRanges.DEFAULT_HP_CUTOFF_KHZ;
        private decimal m_hp_notch =   CyParamRanges.DEFAULT_HP_NOTCH_KHZ;
        private decimal m_lp_cutoff =  CyParamRanges.DEFAULT_LP_CUTOFF_KHZ;
        private decimal m_lp_notch =   CyParamRanges.DEFAULT_LP_NOTCH_KHZ;
        private decimal m_bp_low3db =  CyParamRanges.DEFAULT_BP_LOW3DB_KHZ;
        private decimal m_bp_high3db = CyParamRanges.DEFAULT_BP_HIGH3DB_KHZ;
        private decimal m_bs_center =  CyParamRanges.DEFAULT_BS_CENTER_KHZ;
        private decimal m_bs_3db =     CyParamRanges.DEFAULT_BS_3DB_KHZ;

        private bool m_enableRedraw = false;
        private CheckBox m_cbApplyFilter;

    
        public delegate void ScheduleErrorsHandler(List<CyDRCInfo_v1> schedErrList);
        public ScheduleErrorsHandler SchedulerErrorsChange;

        public bool EnableRedraw
        {
            get
            {
                return this.m_enableRedraw;
            }
            set
            {
                this.m_enableRedraw = value;
                if (this.m_bodeControl != null)
                {
                    this.m_bodeControl.EnableRedraw = value;
                }
            }
        }


        #region CyTabControlWrapper Members

        public override string TabName
        {
            get
            {
                return "Common";
            }
        }

        #endregion

        #region Constructor(s)

        public CyFilterSubtab(CyParameters param, int configNumber)
            : base(param) 
        {
            ConfigNumber = configNumber;

            m_blockParamUpdate = true;
            InitializeComponent();
            this.m_bodeControl = new CyBodeControl(param, ConfigNumber);
            this.m_pnlGraph.Controls.Add(this.m_bodeControl);
            this.m_bodeControl.Dock = DockStyle.Fill;
            SetComponentsState();
            m_blockParamUpdate = false;

            var config = m_params.GetConfig(ConfigNumber);
            config.SideEffectChange += UpdateUI;
            UpdateUIFilterLabels(config);
            UpdateUI();
        }
        public CyFilterSubtab(CyParameters param)
            : this(param, 0)
        {
        }

        #endregion

        public virtual void OnSchedulerErrorsChange(List<CyDRCInfo_v1> drcs)
        {
            ScheduleErrorsHandler handler = SchedulerErrorsChange;
            if (handler != null)
            {
                handler(drcs);
            }
        }

        public void SchedulerUpdate(List<CyDRCInfo_v1> schedErrList)
        {
            this.m_bodeControl.RefreshAll();
            UpdateUI();
        }

        private void InitializeComponent()
        {
            this.components = new System.ComponentModel.Container();
            this.m_cmbFilterType = new System.Windows.Forms.ComboBox();
            this.m_lFilterType = new System.Windows.Forms.Label();
            this.m_l3dB_or_centerFreq = new System.Windows.Forms.Label();
            this.m_lNotch_or_bandwidthFreq = new System.Windows.Forms.Label();
            this.m_nud3dB_or_centerFreq = new System.Windows.Forms.NumericUpDown();
            this.m_nudNotch_or_bandwidthFreq = new System.Windows.Forms.NumericUpDown();
            this.m_filterToolTip = new System.Windows.Forms.ToolTip(this.components);
            this.m_lSampleFreqValue = new System.Windows.Forms.Label();
            this.m_pnlControls = new System.Windows.Forms.Panel();
            this.m_tblControls = new System.Windows.Forms.TableLayoutPanel();
            this.m_lSampleFreq = new System.Windows.Forms.Label();
            this.m_cbApplyFilter = new System.Windows.Forms.CheckBox();
            this.m_pnlGraph = new System.Windows.Forms.Panel();
            ((System.ComponentModel.ISupportInitialize)(this.m_nud3dB_or_centerFreq)).BeginInit();
            ((System.ComponentModel.ISupportInitialize)(this.m_nudNotch_or_bandwidthFreq)).BeginInit();
            this.m_pnlControls.SuspendLayout();
            this.m_tblControls.SuspendLayout();
            this.SuspendLayout();
            // 
            // m_cmbFilterType
            // 
            this.m_cmbFilterType.Anchor = ((System.Windows.Forms.AnchorStyles)((System.Windows.Forms.AnchorStyles.Left | System.Windows.Forms.AnchorStyles.Right)));
            this.m_tblControls.SetColumnSpan(this.m_cmbFilterType, 2);
            this.m_cmbFilterType.DropDownStyle = System.Windows.Forms.ComboBoxStyle.DropDownList;
            this.m_cmbFilterType.FormattingEnabled = true;
            this.m_cmbFilterType.Location = new System.Drawing.Point(183, 26);
            this.m_cmbFilterType.Name = "m_cmbFilterType";
            this.m_cmbFilterType.Size = new System.Drawing.Size(268, 21);
            this.m_cmbFilterType.TabIndex = 3;
            this.m_filterToolTip.SetToolTip(this.m_cmbFilterType, global::Scan_ADC_v1_30.View.cytooltips.filterTypeToolTip);
            this.m_cmbFilterType.SelectedIndexChanged += new System.EventHandler(this.cmb_SelectedIndexChanged);
            // 
            // m_lFilterType
            // 
            this.m_lFilterType.Anchor = System.Windows.Forms.AnchorStyles.Left;
            this.m_lFilterType.AutoSize = true;
            this.m_lFilterType.Location = new System.Drawing.Point(3, 30);
            this.m_lFilterType.Name = "m_lFilterType";
            this.m_lFilterType.Size = new System.Drawing.Size(55, 13);
            this.m_lFilterType.TabIndex = 2;
            this.m_lFilterType.Text = "Filter type:";
            // 
            // m_l3dB_or_centerFreq
            // 
            this.m_l3dB_or_centerFreq.Anchor = System.Windows.Forms.AnchorStyles.Left;
            this.m_l3dB_or_centerFreq.AutoSize = true;
            this.m_l3dB_or_centerFreq.Location = new System.Drawing.Point(3, 56);
            this.m_l3dB_or_centerFreq.Name = "m_l3dB_or_centerFreq";
            this.m_l3dB_or_centerFreq.Size = new System.Drawing.Size(97, 13);
            this.m_l3dB_or_centerFreq.TabIndex = 4;
            this.m_l3dB_or_centerFreq.Text = "Frequency 1 (kHz):";
            // 
            // m_lNotch_or_bandwidthFreq
            // 
            this.m_lNotch_or_bandwidthFreq.Anchor = System.Windows.Forms.AnchorStyles.Left;
            this.m_lNotch_or_bandwidthFreq.AutoSize = true;
            this.m_lNotch_or_bandwidthFreq.Location = new System.Drawing.Point(3, 82);
            this.m_lNotch_or_bandwidthFreq.Name = "m_lNotch_or_bandwidthFreq";
            this.m_lNotch_or_bandwidthFreq.Size = new System.Drawing.Size(97, 13);
            this.m_lNotch_or_bandwidthFreq.TabIndex = 6;
            this.m_lNotch_or_bandwidthFreq.Text = "Frequency 2 (kHz):";
            // 
            // m_nud3dB_or_centerFreq
            // 
            this.m_nud3dB_or_centerFreq.Anchor = System.Windows.Forms.AnchorStyles.Left;
            this.m_nud3dB_or_centerFreq.Increment = new decimal(new int[] {
            10,
            0,
            0,
            0});
            this.m_nud3dB_or_centerFreq.Location = new System.Drawing.Point(183, 53);
            this.m_nud3dB_or_centerFreq.Maximum = new decimal(new int[] {
            10000,
            0,
            0,
            0});
            this.m_nud3dB_or_centerFreq.Name = "m_nud3dB_or_centerFreq";
            this.m_nud3dB_or_centerFreq.Size = new System.Drawing.Size(92, 20);
            this.m_nud3dB_or_centerFreq.TabIndex = 5;
            this.m_nud3dB_or_centerFreq.Value = new decimal(new int[] {
            10,
            0,
            0,
            0});
            this.m_nud3dB_or_centerFreq.TextChanged += new System.EventHandler(this.nud_TextChanged);
            // 
            // m_nudNotch_or_bandwidthFreq
            // 
            this.m_nudNotch_or_bandwidthFreq.Anchor = System.Windows.Forms.AnchorStyles.Left;
            this.m_nudNotch_or_bandwidthFreq.Increment = new decimal(new int[] {
            10,
            0,
            0,
            0});
            this.m_nudNotch_or_bandwidthFreq.Location = new System.Drawing.Point(183, 79);
            this.m_nudNotch_or_bandwidthFreq.Maximum = new decimal(new int[] {
            10000,
            0,
            0,
            0});
            this.m_nudNotch_or_bandwidthFreq.Name = "m_nudNotch_or_bandwidthFreq";
            this.m_nudNotch_or_bandwidthFreq.Size = new System.Drawing.Size(92, 20);
            this.m_nudNotch_or_bandwidthFreq.TabIndex = 7;
            this.m_nudNotch_or_bandwidthFreq.Value = new decimal(new int[] {
            500,
            0,
            0,
            0});
            this.m_nudNotch_or_bandwidthFreq.TextChanged += new System.EventHandler(this.nud_TextChanged);
            // 
            // m_lSampleFreqValue
            // 
            this.m_lSampleFreqValue.Anchor = System.Windows.Forms.AnchorStyles.Left;
            this.m_lSampleFreqValue.AutoSize = true;
            this.m_lSampleFreqValue.Location = new System.Drawing.Point(457, 56);
            this.m_lSampleFreqValue.Name = "m_lSampleFreqValue";
            this.m_lSampleFreqValue.Size = new System.Drawing.Size(46, 13);
            this.m_lSampleFreqValue.TabIndex = 9;
            this.m_lSampleFreqValue.Text = "1000.00";
            this.m_filterToolTip.SetToolTip(this.m_lSampleFreqValue, global::Scan_ADC_v1_30.View.cytooltips.filterSampleFreqToolTip);
            // 
            // m_pnlControls
            // 
            this.m_pnlControls.Controls.Add(this.m_tblControls);
            this.m_pnlControls.Dock = System.Windows.Forms.DockStyle.Top;
            this.m_pnlControls.Location = new System.Drawing.Point(0, 0);
            this.m_pnlControls.Name = "m_pnlControls";
            this.m_pnlControls.Size = new System.Drawing.Size(621, 111);
            this.m_pnlControls.TabIndex = 5;
            // 
            // m_tblControls
            // 
            this.m_tblControls.AutoSize = true;
            this.m_tblControls.ColumnCount = 4;
            this.m_tblControls.ColumnStyles.Add(new System.Windows.Forms.ColumnStyle(System.Windows.Forms.SizeType.Absolute, 180F));
            this.m_tblControls.ColumnStyles.Add(new System.Windows.Forms.ColumnStyle());
            this.m_tblControls.ColumnStyles.Add(new System.Windows.Forms.ColumnStyle());
            this.m_tblControls.ColumnStyles.Add(new System.Windows.Forms.ColumnStyle());
            this.m_tblControls.Controls.Add(this.m_lFilterType, 0, 1);
            this.m_tblControls.Controls.Add(this.m_cmbFilterType, 1, 1);
            this.m_tblControls.Controls.Add(this.m_l3dB_or_centerFreq, 0, 2);
            this.m_tblControls.Controls.Add(this.m_nud3dB_or_centerFreq, 1, 2);
            this.m_tblControls.Controls.Add(this.m_lNotch_or_bandwidthFreq, 0, 3);
            this.m_tblControls.Controls.Add(this.m_nudNotch_or_bandwidthFreq, 1, 3);
            this.m_tblControls.Controls.Add(this.m_lSampleFreq, 2, 2);
            this.m_tblControls.Controls.Add(this.m_lSampleFreqValue, 3, 2);
            this.m_tblControls.Controls.Add(this.m_cbApplyFilter, 1, 0);
            this.m_tblControls.Dock = System.Windows.Forms.DockStyle.Top;
            this.m_tblControls.Location = new System.Drawing.Point(0, 0);
            this.m_tblControls.Name = "m_tblControls";
            this.m_tblControls.RowCount = 4;
            this.m_tblControls.RowStyles.Add(new System.Windows.Forms.RowStyle());
            this.m_tblControls.RowStyles.Add(new System.Windows.Forms.RowStyle());
            this.m_tblControls.RowStyles.Add(new System.Windows.Forms.RowStyle());
            this.m_tblControls.RowStyles.Add(new System.Windows.Forms.RowStyle());
            this.m_tblControls.Size = new System.Drawing.Size(621, 102);
            this.m_tblControls.TabIndex = 7;
            // 
            // m_lSampleFreq
            // 
            this.m_lSampleFreq.Anchor = System.Windows.Forms.AnchorStyles.Left;
            this.m_lSampleFreq.AutoSize = true;
            this.m_lSampleFreq.Location = new System.Drawing.Point(325, 56);
            this.m_lSampleFreq.Name = "m_lSampleFreq";
            this.m_lSampleFreq.Size = new System.Drawing.Size(126, 13);
            this.m_lSampleFreq.TabIndex = 8;
            this.m_lSampleFreq.Text = "Sample Frequency (kHz):";
            // 
            // m_cbApplyFilter
            // 
            this.m_cbApplyFilter.AutoSize = true;
            this.m_cbApplyFilter.Location = new System.Drawing.Point(183, 3);
            this.m_cbApplyFilter.Name = "m_cbApplyFilter";
            this.m_cbApplyFilter.Size = new System.Drawing.Size(136, 17);
            this.m_cbApplyFilter.TabIndex = 1;
            this.m_cbApplyFilter.Text = "Apply filter to channel 0";
            this.m_cbApplyFilter.UseVisualStyleBackColor = true;
            this.m_cbApplyFilter.CheckedChanged += new System.EventHandler(this.cb_CheckedChanged);
            // 
            // m_pnlGraph
            // 
            this.m_pnlGraph.BackColor = System.Drawing.SystemColors.Control;
            this.m_pnlGraph.Dock = System.Windows.Forms.DockStyle.Top;
            this.m_pnlGraph.Location = new System.Drawing.Point(0, 111);
            this.m_pnlGraph.Name = "m_pnlGraph";
            this.m_pnlGraph.Size = new System.Drawing.Size(621, 408);
            this.m_pnlGraph.TabIndex = 6;
            // 
            // CyFilterSubtab
            // 
            this.Controls.Add(this.m_pnlGraph);
            this.Controls.Add(this.m_pnlControls);
            this.Margin = new System.Windows.Forms.Padding(0);
            this.Name = "CyFilterSubtab";
            this.Size = new System.Drawing.Size(621, 519);
            this.Load += new System.EventHandler(this.CyFilterSubtab_Load);
            ((System.ComponentModel.ISupportInitialize)(this.m_nud3dB_or_centerFreq)).EndInit();
            ((System.ComponentModel.ISupportInitialize)(this.m_nudNotch_or_bandwidthFreq)).EndInit();
            this.m_pnlControls.ResumeLayout(false);
            this.m_pnlControls.PerformLayout();
            this.m_tblControls.ResumeLayout(false);
            this.m_tblControls.PerformLayout();
            this.ResumeLayout(false);

        }

        private void SetComponentsState()
        {
            if (m_params != null)
            {
                CyComboUtils.SetEnumDataSource<CyEFilterType>(m_cmbFilterType);
            }
        }

        private void SetToolTips()
        {
            this.m_filterToolTip.SetToolTip(this.m_lFilterType, Scan_ADC_v1_30.View.cytooltips.filterTypeToolTip);
            this.m_filterToolTip.SetToolTip(this.m_cmbFilterType, Scan_ADC_v1_30.View.cytooltips.filterTypeToolTip);
            this.m_filterToolTip.SetToolTip(this.m_lSampleFreq, Scan_ADC_v1_30.View.cytooltips.filterSampleFreqToolTip);
            this.m_filterToolTip.SetToolTip(this.m_lSampleFreqValue, Scan_ADC_v1_30.View.cytooltips.filterSampleFreqToolTip);
        }

        public void UpdateUI()
        {
            m_blockParamUpdate = true;

            CyConfigModel config = m_params.GetConfig(m_configNumber);

            m_cbApplyFilter.Checked
                = (config.ChannelList[0].InputMode == CyEInputMode.FILTER_CHAN)
                ? true : false;

            m_cmbFilterType.SelectedValue = config.FilterType;
            m_nud3dB_or_centerFreq.Value = (decimal)config.FilterDown3OrCenter;
            m_nudNotch_or_bandwidthFreq.Value = (decimal)config.FilterWidthOrNotch;
            m_lSampleFreqValue.Text = config.FilterSample.ToString("##0.00");
            UpdateLocalFilterFreqs();

            if ((config.ChannelList[0].InputMode == CyEInputMode.FILTER_CHAN)
                && (config.FreeRunning == true))
            {
                m_cmbFilterType.Enabled = true;
                m_nud3dB_or_centerFreq.Enabled = true;
                m_nudNotch_or_bandwidthFreq.Enabled = true;
            }
            else
            {
                m_cmbFilterType.Enabled = false;
                m_nud3dB_or_centerFreq.Enabled = false;
                m_nudNotch_or_bandwidthFreq.Enabled = false;
            }

            SetToolTips();
            m_blockParamUpdate = false;
        }

        public int ConfigNumber
        {
            get { return m_configNumber; }
            set { m_configNumber = value; }
        }

        public void cmb_SelectedIndexChanged(object sender, EventArgs e)
        {
            if (m_blockParamUpdate == false)
            {
                CyConfigModel config = m_params.GetConfig(m_configNumber);
                if (sender == m_cmbFilterType)
                {
                    var displayValue
                        = (CyDisplayValue<CyEFilterType>)m_cmbFilterType.SelectedItem;
                    if (displayValue != null)
                    {
                        var tmpBlockUpdateState = m_blockParamUpdate;
                        m_blockParamUpdate = true;
                        switch (displayValue.Value)
                        {
                            case CyEFilterType.HIGH_PASS:
                                m_nud3dB_or_centerFreq.Value = m_hp_cutoff;
                                m_nudNotch_or_bandwidthFreq.Value = m_hp_notch;
                                break;
                            case CyEFilterType.LOW_PASS:
                                m_nud3dB_or_centerFreq.Value = m_lp_cutoff;
                                m_nudNotch_or_bandwidthFreq.Value = m_lp_notch;
                                break;
                            case CyEFilterType.BAND_PASS:
                                m_nud3dB_or_centerFreq.Value = m_bp_low3db;
                                m_nudNotch_or_bandwidthFreq.Value = m_bp_high3db;
                                break;
                            case CyEFilterType.BAND_STOP:
                                m_nud3dB_or_centerFreq.Value = m_bs_center;
                                m_nudNotch_or_bandwidthFreq.Value = m_bs_3db;
                                break;
                            default:
                                break;
                        }
                        m_blockParamUpdate = tmpBlockUpdateState;
                        config.FilterType = displayValue.Value;
                        config.FilterDown3OrCenter = (double)m_nud3dB_or_centerFreq.Value;
                        config.FilterWidthOrNotch = (double)m_nudNotch_or_bandwidthFreq.Value;
                        UpdateUIFilterLabels(config);
                    }
                }

                m_params.SetConfig(m_configNumber, config);

                try
                {
                    ScheduleScan(config);
                }
                catch (CapacitorMapperException)
                {
                    // If capacitor mapping fails, leave config.UabCaps unchanged.
                }

                UpdateUI();
                this.m_bodeControl.RefreshAll();
            }
        }

        private void UpdateUIFilterLabels(CyConfigModel config)
        {
            switch (config.FilterType)
            {
                case CyEFilterType.BAND_PASS:
                    this.m_l3dB_or_centerFreq.Text =
                        global::Scan_ADC_v1_30.View.cytooltips.filterBandPassF1Label;
                    this.m_lNotch_or_bandwidthFreq.Text =
                        global::Scan_ADC_v1_30.View.cytooltips.filterBandPassF2Label;
                    m_filterToolTip.SetToolTip(this.m_nud3dB_or_centerFreq, string.Format(global::Scan_ADC_v1_30.View.cytooltips.filter3dbToolTip, "low "));
                    m_filterToolTip.SetToolTip(this.m_nudNotch_or_bandwidthFreq, string.Format(global::Scan_ADC_v1_30.View.cytooltips.filter3dbToolTip, "high "));
                    break;
                case CyEFilterType.BAND_STOP:
                    this.m_l3dB_or_centerFreq.Text =
                         global::Scan_ADC_v1_30.View.cytooltips.filterBandStopF1Label;
                    this.m_lNotch_or_bandwidthFreq.Text =
                         global::Scan_ADC_v1_30.View.cytooltips.filterBandStopF2Label;
                    m_filterToolTip.SetToolTip(this.m_nud3dB_or_centerFreq, string.Format(global::Scan_ADC_v1_30.View.cytooltips.filter3dbToolTip, ""));
                    m_filterToolTip.SetToolTip(this.m_nudNotch_or_bandwidthFreq, global::Scan_ADC_v1_30.View.cytooltips.filterNotchToolTip);
                    break;
                case CyEFilterType.HIGH_PASS:
                    this.m_l3dB_or_centerFreq.Text =
                         global::Scan_ADC_v1_30.View.cytooltips.filterHighPassF1Label;
                    this.m_lNotch_or_bandwidthFreq.Text =
                         global::Scan_ADC_v1_30.View.cytooltips.filterHighPassF2Label;
                    m_filterToolTip.SetToolTip(this.m_nud3dB_or_centerFreq, global::Scan_ADC_v1_30.View.cytooltips.filterNotchToolTip);
                    m_filterToolTip.SetToolTip(this.m_nudNotch_or_bandwidthFreq, string.Format(global::Scan_ADC_v1_30.View.cytooltips.filter3dbToolTip, ""));
                    break;
                case CyEFilterType.LOW_PASS:
                    this.m_l3dB_or_centerFreq.Text =
                         global::Scan_ADC_v1_30.View.cytooltips.filterLowPassF1Label;
                    this.m_lNotch_or_bandwidthFreq.Text =
                         global::Scan_ADC_v1_30.View.cytooltips.filterLowPassF2Label;
                    m_filterToolTip.SetToolTip(this.m_nud3dB_or_centerFreq, string.Format(global::Scan_ADC_v1_30.View.cytooltips.filter3dbToolTip, ""));
                    m_filterToolTip.SetToolTip(this.m_nudNotch_or_bandwidthFreq, global::Scan_ADC_v1_30.View.cytooltips.filterNotchToolTip);
                    break;
            }
        }

        private void UpdateLocalFilterFreqs()
        {
            var displayValue
                        = (CyDisplayValue<CyEFilterType>)m_cmbFilterType.SelectedItem;
            if (displayValue != null)
            {
                switch (displayValue.Value)
                {
                    case CyEFilterType.HIGH_PASS:
                        m_hp_cutoff = m_nud3dB_or_centerFreq.Value;
                        m_hp_notch = m_nudNotch_or_bandwidthFreq.Value;
                        break;
                    case CyEFilterType.LOW_PASS:
                        m_lp_cutoff = m_nud3dB_or_centerFreq.Value;
                        m_lp_notch = m_nudNotch_or_bandwidthFreq.Value;
                        break;
                    case CyEFilterType.BAND_PASS:
                        m_bp_low3db = m_nud3dB_or_centerFreq.Value;
                        m_bp_high3db = m_nudNotch_or_bandwidthFreq.Value;
                        break;
                    case CyEFilterType.BAND_STOP:
                        m_bs_center = m_nud3dB_or_centerFreq.Value;
                        m_bs_3db = m_nudNotch_or_bandwidthFreq.Value;
                        break;
                    default:
                        break;
                }
            }
        }

        public void nud_TextChanged(object sender, EventArgs e)
        {
            if (m_blockParamUpdate == false)
            {
                bool isUpdateSched = false;
                CyConfigModel config = m_params.GetConfig(m_configNumber);
                if (sender == m_nud3dB_or_centerFreq)
                {
                    config.FilterDown3OrCenter = (double)m_nud3dB_or_centerFreq.Value;
                    isUpdateSched = true;
                }
                else if (sender == m_nudNotch_or_bandwidthFreq)
                {
                    config.FilterWidthOrNotch = (double)m_nudNotch_or_bandwidthFreq.Value;
                    isUpdateSched = true;
                }

                m_params.SetConfig(m_configNumber, config);
                UpdateLocalFilterFreqs();

                if (isUpdateSched)
                {
                    try
                    {
                        ScheduleScan(config);
                    }
                    catch (CapacitorMapperException)
                    {
                        // If capacitor mapping fails, leave config.UabCaps unchanged.
                    }
                }

                UpdateUI();
                this.m_bodeControl.RefreshAll();
            }
        }

        private void cb_CheckedChanged(object sender, EventArgs e)
        {
            if (m_blockParamUpdate == false)
            {
                CyConfigModel config = m_params.GetConfig(m_configNumber);

                if (sender == m_cbApplyFilter)
                {
                    if (m_cbApplyFilter.Checked == true)
                    {
                        config.ChannelList[0].InputMode = CyEInputMode.FILTER_CHAN;
                    }
                    else
                    {
                        config.ChannelList[0].InputMode = CyEInputMode.SINGLE_ENDED_CHAN;
                    }
                }

                m_params.SetConfig(m_configNumber, config);

                ScheduleScan(config);
                config.OnSideEffectChange();
            }
        }

        private void ScheduleScan(CyConfigModel config)
        {
            var isClkExternal = m_params.ExternalClk;
            var clkData = isClkExternal ?
                m_params.ExternalAdcClockData :
                m_params.InternalAdcClockData;
            var schedErrs = config.UpdateScanSchedule(clkData, isClkExternal, m_params.Debug);
            m_params.SetConfig(m_configNumber, config);
            config.UpdateScanRateLimits(clkData, isClkExternal);
            OnSchedulerErrorsChange(schedErrs);
        }

        private void CyFilterSubtab_Load(object sender, EventArgs e)
        {
        }
    }
}

//[] END OF FILE
