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
using System.ComponentModel;
using System.Drawing;
using System.Data;
using System.Globalization;
using System.Linq;
using System.Reflection;
using System.Text;
using System.Windows.Forms;

using CyDesigner.Extensions.Gde;
using CyDesigner.Extensions.Common;


namespace Scan_ADC_v1_30
{
    public class CyConversionSubtab : CyTabControlWrapper
    {
        #region Designer-tracked members

        #endregion Designer-tracked members

        private bool m_blockParamUpdate;
        private ToolTip m_convToolTip;
        private IContainer components;
        public int m_configNumber = 0;
        public TableLayoutPanel m_tlpSubTabConv;
        public GroupBox m_gbTiming;
        private TableLayoutPanel m_tlpTiming;
        public Label m_lValidClockFreq;
        public Label m_lValidHeading;
        public Label m_lValidScanRate;
        private Label m_lConversionTimeNum;
        public Label m_lActualHeading;
        private Label m_lConversionTime;
        public Label m_lActualClockFreq;
        public Label m_lActualSampleRate;
        public NumericUpDown m_nudSampleRate;
        private Label label1;
        private Label label2;
        public GroupBox m_gbChannelConfiguration;
        private TableLayoutPanel tableLayoutPanel3;
        public NumericUpDown m_nudSequencedChannels;
        public Label m_lSequencedChannels;
        public DataGridView m_dgvChannels;
        public GroupBox m_gbSampleMode;
        public CheckBox m_cbUseSoc;
        public RadioButton m_rbOneShot;
        public RadioButton m_rbFreeRunning;
        public GroupBox m_gbInputRange;
        private TableLayoutPanel tableLayoutPanel2;
        public Label m_lVref;
        public Label m_lSERangeRow;
        private CheckBox m_cbVrefBypass;
        public Label m_lSECodeRange;
        public Label m_lSEVoltRange;
        public Label m_lDiffRangeRow;
        public ComboBox m_cmbVrefSource;
        public ComboBox m_cmbVnegSource;
        public Label m_lVneg;
        public Label m_lDiffVoltRange;
        public Label m_lDiffCodeRange;
        public Label m_lCodeRangeHeading;
        public Label m_lVoltRangeHeading;
        private Panel m_pVrefVoltage;
        private Label m_lVrefVoltage;
        public NumericUpDown m_nudVrefVoltage;
        public GroupBox m_gbResultDataFormat;
        private TableLayoutPanel m_tlpResultFormat;
        public ComboBox m_cmbAlternateResolution;
        public Label m_lDiffResultFormat;
        public Label m_lAlternateResolution;
        public ComboBox m_cmbDiffResultFormat;
        public ComboBox m_cmbAveragingMode;
        public Label m_lSEResultFormat;
        public Label m_lAveragingMode;
        public ComboBox m_cmbSEResultFormat;
        public ComboBox m_cmbSamplesAveraged;
        public Label m_lSamplesAveraged;
        public GroupBox m_gbInterruptLimits;
        private TableLayoutPanel tableLayoutPanel1;
        public Label m_lCompareMode;
        public NumericUpDown m_nudHighLimit;
        public Label m_lSELowLimitVolts;
        public Label m_lLowLimit;
        public Label m_lDiffLowLimitVolts;
        public NumericUpDown m_nudLowLimit;
        public Label m_lSELimitRow;
        public Label m_lHighLimit;
        public Label m_lDiffLimitRow;
        public Label m_lDiffHighLimitVolts;
        public Label m_lSEHighLimitVolts;
        public ComboBox m_cmbCompareMode;
        private Label m_lVrefErr;
        private Label m_lDiffAvgLimitRow;
        private Label m_lSEAvgLimitRow;
        private Label m_lDiffAvgLowLimitVolts;
        private Label m_lSEAvgLowLimitVolts;
        private Label m_lDiffAvgHighLimitVolts;
        private Label m_lSEAvgHighLimitVolts;
        private DataGridViewTextBoxColumn m_dgvcChannel;
        private DataGridViewCheckBoxColumn m_dgvcEnable;
        private DataGridViewComboBoxColumn m_dgvcResolution;
        private DataGridViewComboBoxColumn m_dgvcInputMode;
        private DataGridViewCheckBoxColumn m_dgvcAverage;
        private DataGridViewTextBoxColumn m_dgvcAcqTime;
        private DataGridViewTextBoxColumn m_dgvcActualAcq;
        private DataGridViewTextBoxColumn m_dgvcMaxInResist;
        private DataGridViewCheckBoxColumn m_dgvcLimitInterrupt;
        private DataGridViewCheckBoxColumn m_dgvcSaturationInterrupt;
    
        public delegate void ScheduleErrorsHandler(List<CyDRCInfo_v1> schedErrList);
        public ScheduleErrorsHandler SchedulerErrorsChange;

        public int ConfigNumber
        {
            get { return m_configNumber; }
            set { m_configNumber = value; }
        }

        #region CyTabControlWrapper Members
        public override string TabName
        {
            get
            {
                return global::Scan_ADC_v1_30.View.cytooltips.conversionTabName;
            }
        }
        #endregion

        #region Constructor(s)

        public CyConversionSubtab(CyParameters param, int configNumber)
            : base(param)
        {
            ConfigNumber = configNumber;
            var config = m_params.GetConfig(ConfigNumber);
            
            m_blockParamUpdate = true;
            InitializeComponent();
            SetComponentsState();
            ScheduleScan(config);
            m_blockParamUpdate = false;

            m_params.AdcClockSourceChange += AdcClockSourceChanged;
            m_params.SideEffectChange += UpdateUI;
            config.SideEffectChange += UpdateUI;

            UpdateUI();
        }

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
            UpdateUI();
        }

        public CyConversionSubtab(CyParameters param)
            : this(param, 0) 
        {
        }

        #endregion

        private void InitializeComponent()
        {
            this.components = new System.ComponentModel.Container();
            System.Windows.Forms.DataGridViewCellStyle dataGridViewCellStyle1 = new System.Windows.Forms.DataGridViewCellStyle();
            System.Windows.Forms.DataGridViewCellStyle dataGridViewCellStyle4 = new System.Windows.Forms.DataGridViewCellStyle();
            System.Windows.Forms.DataGridViewCellStyle dataGridViewCellStyle2 = new System.Windows.Forms.DataGridViewCellStyle();
            System.Windows.Forms.DataGridViewCellStyle dataGridViewCellStyle3 = new System.Windows.Forms.DataGridViewCellStyle();
            this.m_convToolTip = new System.Windows.Forms.ToolTip(this.components);
            this.m_cmbCompareMode = new System.Windows.Forms.ComboBox();
            this.m_nudLowLimit = new System.Windows.Forms.NumericUpDown();
            this.m_nudHighLimit = new System.Windows.Forms.NumericUpDown();
            this.m_cmbSamplesAveraged = new System.Windows.Forms.ComboBox();
            this.m_cmbSEResultFormat = new System.Windows.Forms.ComboBox();
            this.m_cmbAveragingMode = new System.Windows.Forms.ComboBox();
            this.m_cmbDiffResultFormat = new System.Windows.Forms.ComboBox();
            this.m_cmbAlternateResolution = new System.Windows.Forms.ComboBox();
            this.m_nudVrefVoltage = new System.Windows.Forms.NumericUpDown();
            this.m_cmbVnegSource = new System.Windows.Forms.ComboBox();
            this.m_cmbVrefSource = new System.Windows.Forms.ComboBox();
            this.m_cbVrefBypass = new System.Windows.Forms.CheckBox();
            this.m_rbFreeRunning = new System.Windows.Forms.RadioButton();
            this.m_rbOneShot = new System.Windows.Forms.RadioButton();
            this.m_lSequencedChannels = new System.Windows.Forms.Label();
            this.m_nudSequencedChannels = new System.Windows.Forms.NumericUpDown();
            this.m_cbUseSoc = new System.Windows.Forms.CheckBox();
            this.m_tlpSubTabConv = new System.Windows.Forms.TableLayoutPanel();
            this.m_gbTiming = new System.Windows.Forms.GroupBox();
            this.m_tlpTiming = new System.Windows.Forms.TableLayoutPanel();
            this.m_lValidClockFreq = new System.Windows.Forms.Label();
            this.m_lValidHeading = new System.Windows.Forms.Label();
            this.m_lValidScanRate = new System.Windows.Forms.Label();
            this.m_lConversionTimeNum = new System.Windows.Forms.Label();
            this.m_lActualHeading = new System.Windows.Forms.Label();
            this.m_lConversionTime = new System.Windows.Forms.Label();
            this.m_lActualClockFreq = new System.Windows.Forms.Label();
            this.m_lActualSampleRate = new System.Windows.Forms.Label();
            this.m_nudSampleRate = new System.Windows.Forms.NumericUpDown();
            this.label1 = new System.Windows.Forms.Label();
            this.label2 = new System.Windows.Forms.Label();
            this.m_gbChannelConfiguration = new System.Windows.Forms.GroupBox();
            this.tableLayoutPanel3 = new System.Windows.Forms.TableLayoutPanel();
            this.m_dgvChannels = new System.Windows.Forms.DataGridView();
            this.m_dgvcChannel = new System.Windows.Forms.DataGridViewTextBoxColumn();
            this.m_dgvcEnable = new System.Windows.Forms.DataGridViewCheckBoxColumn();
            this.m_dgvcResolution = new System.Windows.Forms.DataGridViewComboBoxColumn();
            this.m_dgvcInputMode = new System.Windows.Forms.DataGridViewComboBoxColumn();
            this.m_dgvcAverage = new System.Windows.Forms.DataGridViewCheckBoxColumn();
            this.m_dgvcAcqTime = new System.Windows.Forms.DataGridViewTextBoxColumn();
            this.m_dgvcActualAcq = new System.Windows.Forms.DataGridViewTextBoxColumn();
            this.m_dgvcMaxInResist = new System.Windows.Forms.DataGridViewTextBoxColumn();
            this.m_dgvcLimitInterrupt = new System.Windows.Forms.DataGridViewCheckBoxColumn();
            this.m_dgvcSaturationInterrupt = new System.Windows.Forms.DataGridViewCheckBoxColumn();
            this.m_gbSampleMode = new System.Windows.Forms.GroupBox();
            this.m_gbInputRange = new System.Windows.Forms.GroupBox();
            this.tableLayoutPanel2 = new System.Windows.Forms.TableLayoutPanel();
            this.m_lSEVoltRange = new System.Windows.Forms.Label();
            this.m_lVref = new System.Windows.Forms.Label();
            this.m_lSERangeRow = new System.Windows.Forms.Label();
            this.m_lSECodeRange = new System.Windows.Forms.Label();
            this.m_lDiffRangeRow = new System.Windows.Forms.Label();
            this.m_lVneg = new System.Windows.Forms.Label();
            this.m_lDiffVoltRange = new System.Windows.Forms.Label();
            this.m_lDiffCodeRange = new System.Windows.Forms.Label();
            this.m_lCodeRangeHeading = new System.Windows.Forms.Label();
            this.m_lVoltRangeHeading = new System.Windows.Forms.Label();
            this.m_pVrefVoltage = new System.Windows.Forms.Panel();
            this.m_lVrefVoltage = new System.Windows.Forms.Label();
            this.m_lVrefErr = new System.Windows.Forms.Label();
            this.m_gbResultDataFormat = new System.Windows.Forms.GroupBox();
            this.m_tlpResultFormat = new System.Windows.Forms.TableLayoutPanel();
            this.m_lDiffResultFormat = new System.Windows.Forms.Label();
            this.m_lAlternateResolution = new System.Windows.Forms.Label();
            this.m_lSEResultFormat = new System.Windows.Forms.Label();
            this.m_lAveragingMode = new System.Windows.Forms.Label();
            this.m_lSamplesAveraged = new System.Windows.Forms.Label();
            this.m_gbInterruptLimits = new System.Windows.Forms.GroupBox();
            this.tableLayoutPanel1 = new System.Windows.Forms.TableLayoutPanel();
            this.m_lCompareMode = new System.Windows.Forms.Label();
            this.m_lSELowLimitVolts = new System.Windows.Forms.Label();
            this.m_lLowLimit = new System.Windows.Forms.Label();
            this.m_lDiffLowLimitVolts = new System.Windows.Forms.Label();
            this.m_lHighLimit = new System.Windows.Forms.Label();
            this.m_lDiffLimitRow = new System.Windows.Forms.Label();
            this.m_lDiffHighLimitVolts = new System.Windows.Forms.Label();
            this.m_lSEHighLimitVolts = new System.Windows.Forms.Label();
            this.m_lSELimitRow = new System.Windows.Forms.Label();
            this.m_lDiffAvgLimitRow = new System.Windows.Forms.Label();
            this.m_lSEAvgLimitRow = new System.Windows.Forms.Label();
            this.m_lDiffAvgLowLimitVolts = new System.Windows.Forms.Label();
            this.m_lSEAvgLowLimitVolts = new System.Windows.Forms.Label();
            this.m_lDiffAvgHighLimitVolts = new System.Windows.Forms.Label();
            this.m_lSEAvgHighLimitVolts = new System.Windows.Forms.Label();
            ((System.ComponentModel.ISupportInitialize)(this.m_nudLowLimit)).BeginInit();
            ((System.ComponentModel.ISupportInitialize)(this.m_nudHighLimit)).BeginInit();
            ((System.ComponentModel.ISupportInitialize)(this.m_nudVrefVoltage)).BeginInit();
            ((System.ComponentModel.ISupportInitialize)(this.m_nudSequencedChannels)).BeginInit();
            this.m_tlpSubTabConv.SuspendLayout();
            this.m_gbTiming.SuspendLayout();
            this.m_tlpTiming.SuspendLayout();
            ((System.ComponentModel.ISupportInitialize)(this.m_nudSampleRate)).BeginInit();
            this.m_gbChannelConfiguration.SuspendLayout();
            this.tableLayoutPanel3.SuspendLayout();
            ((System.ComponentModel.ISupportInitialize)(this.m_dgvChannels)).BeginInit();
            this.m_gbSampleMode.SuspendLayout();
            this.m_gbInputRange.SuspendLayout();
            this.tableLayoutPanel2.SuspendLayout();
            this.m_pVrefVoltage.SuspendLayout();
            this.m_gbResultDataFormat.SuspendLayout();
            this.m_tlpResultFormat.SuspendLayout();
            this.m_gbInterruptLimits.SuspendLayout();
            this.tableLayoutPanel1.SuspendLayout();
            this.SuspendLayout();
            // 
            // m_convToolTip
            // 
            this.m_convToolTip.Popup += new System.Windows.Forms.PopupEventHandler(this.m_convToolTip_Popup);
            // 
            // m_cmbCompareMode
            // 
            this.m_cmbCompareMode.Anchor = ((System.Windows.Forms.AnchorStyles)((System.Windows.Forms.AnchorStyles.Left | System.Windows.Forms.AnchorStyles.Right)));
            this.tableLayoutPanel1.SetColumnSpan(this.m_cmbCompareMode, 3);
            this.m_cmbCompareMode.DropDownStyle = System.Windows.Forms.ComboBoxStyle.DropDownList;
            this.m_cmbCompareMode.FormattingEnabled = true;
            this.m_cmbCompareMode.Items.AddRange(new object[] {
            "(Result < Low) or (High <= Result)"});
            this.m_cmbCompareMode.Location = new System.Drawing.Point(90, 3);
            this.m_cmbCompareMode.Name = "m_cmbCompareMode";
            this.m_cmbCompareMode.Size = new System.Drawing.Size(258, 21);
            this.m_cmbCompareMode.TabIndex = 1;
            this.m_convToolTip.SetToolTip(this.m_cmbCompareMode, "Use clock frequency to derive sample rate.");
            this.m_cmbCompareMode.SelectedIndexChanged += new System.EventHandler(this.cmb_SelectedIndexChanged);
            // 
            // m_nudLowLimit
            // 
            this.m_nudLowLimit.Anchor = ((System.Windows.Forms.AnchorStyles)((System.Windows.Forms.AnchorStyles.Left | System.Windows.Forms.AnchorStyles.Right)));
            this.m_nudLowLimit.Hexadecimal = true;
            this.m_nudLowLimit.Location = new System.Drawing.Point(90, 30);
            this.m_nudLowLimit.Maximum = new decimal(new int[] {
            65535,
            0,
            0,
            0});
            this.m_nudLowLimit.MaximumSize = new System.Drawing.Size(52, 0);
            this.m_nudLowLimit.MinimumSize = new System.Drawing.Size(52, 0);
            this.m_nudLowLimit.Name = "m_nudLowLimit";
            this.m_nudLowLimit.Size = new System.Drawing.Size(52, 20);
            this.m_nudLowLimit.TabIndex = 2;
            this.m_convToolTip.SetToolTip(this.m_nudLowLimit, "Use clock frequency to derive sample rate.");
            this.m_nudLowLimit.TextChanged += new System.EventHandler(this.nud_TextChanged);
            // 
            // m_nudHighLimit
            // 
            this.m_nudHighLimit.Anchor = ((System.Windows.Forms.AnchorStyles)((System.Windows.Forms.AnchorStyles.Left | System.Windows.Forms.AnchorStyles.Right)));
            this.m_nudHighLimit.Hexadecimal = true;
            this.m_nudHighLimit.Location = new System.Drawing.Point(254, 30);
            this.m_nudHighLimit.Maximum = new decimal(new int[] {
            65535,
            0,
            0,
            0});
            this.m_nudHighLimit.MaximumSize = new System.Drawing.Size(52, 0);
            this.m_nudHighLimit.MinimumSize = new System.Drawing.Size(52, 0);
            this.m_nudHighLimit.Name = "m_nudHighLimit";
            this.m_nudHighLimit.Size = new System.Drawing.Size(52, 20);
            this.m_nudHighLimit.TabIndex = 3;
            this.m_convToolTip.SetToolTip(this.m_nudHighLimit, "Use clock frequency to derive sample rate.");
            this.m_nudHighLimit.Value = new decimal(new int[] {
            65535,
            0,
            0,
            0});
            this.m_nudHighLimit.TextChanged += new System.EventHandler(this.nud_TextChanged);
            // 
            // m_cmbSamplesAveraged
            // 
            this.m_cmbSamplesAveraged.DropDownStyle = System.Windows.Forms.ComboBoxStyle.DropDownList;
            this.m_cmbSamplesAveraged.FormattingEnabled = true;
            this.m_cmbSamplesAveraged.Location = new System.Drawing.Point(109, 57);
            this.m_cmbSamplesAveraged.Name = "m_cmbSamplesAveraged";
            this.m_cmbSamplesAveraged.Size = new System.Drawing.Size(143, 21);
            this.m_cmbSamplesAveraged.TabIndex = 3;
            this.m_convToolTip.SetToolTip(this.m_cmbSamplesAveraged, "Use clock frequency to derive sample rate.");
            this.m_cmbSamplesAveraged.SelectedIndexChanged += new System.EventHandler(this.cmb_SelectedIndexChanged);
            // 
            // m_cmbSEResultFormat
            // 
            this.m_cmbSEResultFormat.DropDownStyle = System.Windows.Forms.ComboBoxStyle.DropDownList;
            this.m_cmbSEResultFormat.FormattingEnabled = true;
            this.m_cmbSEResultFormat.Location = new System.Drawing.Point(109, 30);
            this.m_cmbSEResultFormat.Margin = new System.Windows.Forms.Padding(3, 3, 19, 3);
            this.m_cmbSEResultFormat.Name = "m_cmbSEResultFormat";
            this.m_cmbSEResultFormat.Size = new System.Drawing.Size(143, 21);
            this.m_cmbSEResultFormat.TabIndex = 2;
            this.m_convToolTip.SetToolTip(this.m_cmbSEResultFormat, "Use clock frequency to derive sample rate.");
            this.m_cmbSEResultFormat.SelectedIndexChanged += new System.EventHandler(this.cmb_SelectedIndexChanged);
            // 
            // m_cmbAveragingMode
            // 
            this.m_cmbAveragingMode.DropDownStyle = System.Windows.Forms.ComboBoxStyle.DropDownList;
            this.m_cmbAveragingMode.FormattingEnabled = true;
            this.m_cmbAveragingMode.Location = new System.Drawing.Point(109, 84);
            this.m_cmbAveragingMode.Name = "m_cmbAveragingMode";
            this.m_cmbAveragingMode.Size = new System.Drawing.Size(143, 21);
            this.m_cmbAveragingMode.TabIndex = 4;
            this.m_convToolTip.SetToolTip(this.m_cmbAveragingMode, "Use clock frequency to derive sample rate.");
            this.m_cmbAveragingMode.SelectedIndexChanged += new System.EventHandler(this.cmb_SelectedIndexChanged);
            // 
            // m_cmbDiffResultFormat
            // 
            this.m_cmbDiffResultFormat.DropDownStyle = System.Windows.Forms.ComboBoxStyle.DropDownList;
            this.m_cmbDiffResultFormat.FormattingEnabled = true;
            this.m_cmbDiffResultFormat.Location = new System.Drawing.Point(109, 3);
            this.m_cmbDiffResultFormat.Name = "m_cmbDiffResultFormat";
            this.m_cmbDiffResultFormat.Size = new System.Drawing.Size(143, 21);
            this.m_cmbDiffResultFormat.TabIndex = 1;
            this.m_convToolTip.SetToolTip(this.m_cmbDiffResultFormat, "Use clock frequency to derive sample rate.");
            this.m_cmbDiffResultFormat.SelectedIndexChanged += new System.EventHandler(this.cmb_SelectedIndexChanged);
            // 
            // m_cmbAlternateResolution
            // 
            this.m_cmbAlternateResolution.DropDownStyle = System.Windows.Forms.ComboBoxStyle.DropDownList;
            this.m_cmbAlternateResolution.FormattingEnabled = true;
            this.m_cmbAlternateResolution.Location = new System.Drawing.Point(109, 111);
            this.m_cmbAlternateResolution.Name = "m_cmbAlternateResolution";
            this.m_cmbAlternateResolution.Size = new System.Drawing.Size(143, 21);
            this.m_cmbAlternateResolution.TabIndex = 5;
            this.m_convToolTip.SetToolTip(this.m_cmbAlternateResolution, "Use clock frequency to derive sample rate.");
            this.m_cmbAlternateResolution.SelectedIndexChanged += new System.EventHandler(this.cmb_SelectedIndexChanged);
            // 
            // m_nudVrefVoltage
            // 
            this.m_nudVrefVoltage.DecimalPlaces = 3;
            this.m_nudVrefVoltage.Dock = System.Windows.Forms.DockStyle.Right;
            this.m_nudVrefVoltage.Location = new System.Drawing.Point(2, 0);
            this.m_nudVrefVoltage.Maximum = new decimal(new int[] {
            55,
            0,
            0,
            65536});
            this.m_nudVrefVoltage.MaximumSize = new System.Drawing.Size(52, 0);
            this.m_nudVrefVoltage.MinimumSize = new System.Drawing.Size(50, 0);
            this.m_nudVrefVoltage.Name = "m_nudVrefVoltage";
            this.m_nudVrefVoltage.Size = new System.Drawing.Size(52, 20);
            this.m_nudVrefVoltage.TabIndex = 2;
            this.m_convToolTip.SetToolTip(this.m_nudVrefVoltage, "Use clock frequency to derive sample rate.");
            this.m_nudVrefVoltage.Visible = false;
            this.m_nudVrefVoltage.TextChanged += new System.EventHandler(this.nud_TextChanged);
            // 
            // m_cmbVnegSource
            // 
            this.m_cmbVnegSource.Anchor = ((System.Windows.Forms.AnchorStyles)((System.Windows.Forms.AnchorStyles.Left | System.Windows.Forms.AnchorStyles.Right)));
            this.m_cmbVnegSource.DropDownStyle = System.Windows.Forms.ComboBoxStyle.DropDownList;
            this.m_cmbVnegSource.FormattingEnabled = true;
            this.m_cmbVnegSource.Location = new System.Drawing.Point(81, 53);
            this.m_cmbVnegSource.Name = "m_cmbVnegSource";
            this.m_cmbVnegSource.Size = new System.Drawing.Size(171, 21);
            this.m_cmbVnegSource.TabIndex = 4;
            this.m_convToolTip.SetToolTip(this.m_cmbVnegSource, "Use clock frequency to derive sample rate.");
            this.m_cmbVnegSource.SelectedIndexChanged += new System.EventHandler(this.cmb_SelectedIndexChanged);
            // 
            // m_cmbVrefSource
            // 
            this.m_cmbVrefSource.Anchor = ((System.Windows.Forms.AnchorStyles)((System.Windows.Forms.AnchorStyles.Left | System.Windows.Forms.AnchorStyles.Right)));
            this.m_cmbVrefSource.DropDownStyle = System.Windows.Forms.ComboBoxStyle.DropDownList;
            this.m_cmbVrefSource.FormattingEnabled = true;
            this.m_cmbVrefSource.Location = new System.Drawing.Point(81, 3);
            this.m_cmbVrefSource.Name = "m_cmbVrefSource";
            this.m_cmbVrefSource.Size = new System.Drawing.Size(171, 21);
            this.m_cmbVrefSource.TabIndex = 1;
            this.m_convToolTip.SetToolTip(this.m_cmbVrefSource, "Use clock frequency to derive sample rate.");
            this.m_cmbVrefSource.SelectedIndexChanged += new System.EventHandler(this.cmb_SelectedIndexChanged);
            // 
            // m_cbVrefBypass
            // 
            this.m_cbVrefBypass.AutoSize = true;
            this.m_cbVrefBypass.Location = new System.Drawing.Point(81, 30);
            this.m_cbVrefBypass.Margin = new System.Windows.Forms.Padding(3, 3, 19, 3);
            this.m_cbVrefBypass.Name = "m_cbVrefBypass";
            this.m_cbVrefBypass.Size = new System.Drawing.Size(81, 17);
            this.m_cbVrefBypass.TabIndex = 3;
            this.m_cbVrefBypass.Text = "Vref bypass";
            this.m_convToolTip.SetToolTip(this.m_cbVrefBypass, "Use clock frequency to derive sample rate.");
            this.m_cbVrefBypass.UseVisualStyleBackColor = true;
            this.m_cbVrefBypass.CheckedChanged += new System.EventHandler(this.cb_CheckedChanged);
            // 
            // m_rbFreeRunning
            // 
            this.m_rbFreeRunning.AutoSize = true;
            this.m_rbFreeRunning.Location = new System.Drawing.Point(6, 19);
            this.m_rbFreeRunning.Name = "m_rbFreeRunning";
            this.m_rbFreeRunning.Size = new System.Drawing.Size(78, 17);
            this.m_rbFreeRunning.TabIndex = 1;
            this.m_rbFreeRunning.TabStop = true;
            this.m_rbFreeRunning.Text = "Continuous";
            this.m_convToolTip.SetToolTip(this.m_rbFreeRunning, "Use clock frequency to derive sample rate.");
            this.m_rbFreeRunning.UseVisualStyleBackColor = true;
            this.m_rbFreeRunning.CheckedChanged += new System.EventHandler(this.rb_CheckedChanged);
            // 
            // m_rbOneShot
            // 
            this.m_rbOneShot.AutoSize = true;
            this.m_rbOneShot.Location = new System.Drawing.Point(6, 42);
            this.m_rbOneShot.Name = "m_rbOneShot";
            this.m_rbOneShot.Size = new System.Drawing.Size(77, 17);
            this.m_rbOneShot.TabIndex = 1;
            this.m_rbOneShot.TabStop = true;
            this.m_rbOneShot.Text = "Single shot";
            this.m_convToolTip.SetToolTip(this.m_rbOneShot, "Use clock frequency to derive sample rate.");
            this.m_rbOneShot.UseVisualStyleBackColor = true;
            this.m_rbOneShot.CheckedChanged += new System.EventHandler(this.rb_CheckedChanged);
            // 
            // m_lSequencedChannels
            // 
            this.m_lSequencedChannels.Anchor = System.Windows.Forms.AnchorStyles.Left;
            this.m_lSequencedChannels.AutoSize = true;
            this.m_lSequencedChannels.Location = new System.Drawing.Point(3, 6);
            this.m_lSequencedChannels.Name = "m_lSequencedChannels";
            this.m_lSequencedChannels.Size = new System.Drawing.Size(105, 13);
            this.m_lSequencedChannels.TabIndex = 5;
            this.m_lSequencedChannels.Text = "Number of channels:";
            this.m_convToolTip.SetToolTip(this.m_lSequencedChannels, "Use clock frequency to derive sample rate.");
            // 
            // m_nudSequencedChannels
            // 
            this.m_nudSequencedChannels.Anchor = System.Windows.Forms.AnchorStyles.Left;
            this.m_nudSequencedChannels.Location = new System.Drawing.Point(114, 3);
            this.m_nudSequencedChannels.Name = "m_nudSequencedChannels";
            this.m_nudSequencedChannels.Size = new System.Drawing.Size(39, 20);
            this.m_nudSequencedChannels.TabIndex = 1;
            this.m_convToolTip.SetToolTip(this.m_nudSequencedChannels, "Use clock frequency to derive sample rate.");
            this.m_nudSequencedChannels.ValueChanged += new System.EventHandler(this.nud_TextChanged);
            // 
            // m_cbUseSoc
            // 
            this.m_cbUseSoc.AutoSize = true;
            this.m_cbUseSoc.Location = new System.Drawing.Point(6, 65);
            this.m_cbUseSoc.Name = "m_cbUseSoc";
            this.m_cbUseSoc.Size = new System.Drawing.Size(104, 17);
            this.m_cbUseSoc.TabIndex = 2;
            this.m_cbUseSoc.Text = "Use soc terminal";
            this.m_cbUseSoc.UseVisualStyleBackColor = true;
            this.m_cbUseSoc.CheckedChanged += new System.EventHandler(this.cb_CheckedChanged);
            // 
            // m_tlpSubTabConv
            // 
            this.m_tlpSubTabConv.Anchor = ((System.Windows.Forms.AnchorStyles)((((System.Windows.Forms.AnchorStyles.Top | System.Windows.Forms.AnchorStyles.Bottom) 
            | System.Windows.Forms.AnchorStyles.Left) 
            | System.Windows.Forms.AnchorStyles.Right)));
            this.m_tlpSubTabConv.AutoSize = true;
            this.m_tlpSubTabConv.AutoSizeMode = System.Windows.Forms.AutoSizeMode.GrowAndShrink;
            this.m_tlpSubTabConv.ColumnCount = 3;
            this.m_tlpSubTabConv.ColumnStyles.Add(new System.Windows.Forms.ColumnStyle());
            this.m_tlpSubTabConv.ColumnStyles.Add(new System.Windows.Forms.ColumnStyle());
            this.m_tlpSubTabConv.ColumnStyles.Add(new System.Windows.Forms.ColumnStyle());
            this.m_tlpSubTabConv.Controls.Add(this.m_gbTiming, 0, 0);
            this.m_tlpSubTabConv.Controls.Add(this.m_gbChannelConfiguration, 0, 3);
            this.m_tlpSubTabConv.Controls.Add(this.m_gbSampleMode, 2, 0);
            this.m_tlpSubTabConv.Controls.Add(this.m_gbInputRange, 0, 1);
            this.m_tlpSubTabConv.Controls.Add(this.m_gbResultDataFormat, 0, 2);
            this.m_tlpSubTabConv.Controls.Add(this.m_gbInterruptLimits, 1, 2);
            this.m_tlpSubTabConv.Location = new System.Drawing.Point(3, 3);
            this.m_tlpSubTabConv.MinimumSize = new System.Drawing.Size(1, 1);
            this.m_tlpSubTabConv.Name = "m_tlpSubTabConv";
            this.m_tlpSubTabConv.RowCount = 4;
            this.m_tlpSubTabConv.RowStyles.Add(new System.Windows.Forms.RowStyle());
            this.m_tlpSubTabConv.RowStyles.Add(new System.Windows.Forms.RowStyle());
            this.m_tlpSubTabConv.RowStyles.Add(new System.Windows.Forms.RowStyle());
            this.m_tlpSubTabConv.RowStyles.Add(new System.Windows.Forms.RowStyle());
            this.m_tlpSubTabConv.Size = new System.Drawing.Size(640, 530);
            this.m_tlpSubTabConv.TabIndex = 7;
            // 
            // m_gbTiming
            // 
            this.m_gbTiming.Anchor = ((System.Windows.Forms.AnchorStyles)((((System.Windows.Forms.AnchorStyles.Top | System.Windows.Forms.AnchorStyles.Bottom) 
            | System.Windows.Forms.AnchorStyles.Left) 
            | System.Windows.Forms.AnchorStyles.Right)));
            this.m_gbTiming.AutoSize = true;
            this.m_gbTiming.AutoSizeMode = System.Windows.Forms.AutoSizeMode.GrowAndShrink;
            this.m_tlpSubTabConv.SetColumnSpan(this.m_gbTiming, 2);
            this.m_gbTiming.Controls.Add(this.m_tlpTiming);
            this.m_gbTiming.Location = new System.Drawing.Point(0, 3);
            this.m_gbTiming.Margin = new System.Windows.Forms.Padding(0, 3, 3, 3);
            this.m_gbTiming.MinimumSize = new System.Drawing.Size(425, 87);
            this.m_gbTiming.Name = "m_gbTiming";
            this.m_gbTiming.Size = new System.Drawing.Size(518, 104);
            this.m_gbTiming.TabIndex = 1;
            this.m_gbTiming.TabStop = false;
            this.m_gbTiming.Text = "Timing";
            // 
            // m_tlpTiming
            // 
            this.m_tlpTiming.AutoSize = true;
            this.m_tlpTiming.AutoSizeMode = System.Windows.Forms.AutoSizeMode.GrowAndShrink;
            this.m_tlpTiming.ColumnCount = 4;
            this.m_tlpTiming.ColumnStyles.Add(new System.Windows.Forms.ColumnStyle());
            this.m_tlpTiming.ColumnStyles.Add(new System.Windows.Forms.ColumnStyle());
            this.m_tlpTiming.ColumnStyles.Add(new System.Windows.Forms.ColumnStyle());
            this.m_tlpTiming.ColumnStyles.Add(new System.Windows.Forms.ColumnStyle());
            this.m_tlpTiming.Controls.Add(this.m_lValidClockFreq, 3, 2);
            this.m_tlpTiming.Controls.Add(this.m_lValidHeading, 3, 0);
            this.m_tlpTiming.Controls.Add(this.m_lValidScanRate, 3, 1);
            this.m_tlpTiming.Controls.Add(this.m_lConversionTimeNum, 2, 3);
            this.m_tlpTiming.Controls.Add(this.m_lActualHeading, 2, 0);
            this.m_tlpTiming.Controls.Add(this.m_lConversionTime, 0, 3);
            this.m_tlpTiming.Controls.Add(this.m_lActualClockFreq, 2, 2);
            this.m_tlpTiming.Controls.Add(this.m_lActualSampleRate, 2, 1);
            this.m_tlpTiming.Controls.Add(this.m_nudSampleRate, 1, 1);
            this.m_tlpTiming.Controls.Add(this.label1, 0, 1);
            this.m_tlpTiming.Controls.Add(this.label2, 0, 2);
            this.m_tlpTiming.Dock = System.Windows.Forms.DockStyle.Fill;
            this.m_tlpTiming.GrowStyle = System.Windows.Forms.TableLayoutPanelGrowStyle.AddColumns;
            this.m_tlpTiming.Location = new System.Drawing.Point(3, 16);
            this.m_tlpTiming.Name = "m_tlpTiming";
            this.m_tlpTiming.RowCount = 5;
            this.m_tlpTiming.RowStyles.Add(new System.Windows.Forms.RowStyle());
            this.m_tlpTiming.RowStyles.Add(new System.Windows.Forms.RowStyle());
            this.m_tlpTiming.RowStyles.Add(new System.Windows.Forms.RowStyle());
            this.m_tlpTiming.RowStyles.Add(new System.Windows.Forms.RowStyle());
            this.m_tlpTiming.RowStyles.Add(new System.Windows.Forms.RowStyle(System.Windows.Forms.SizeType.Absolute, 20F));
            this.m_tlpTiming.Size = new System.Drawing.Size(512, 85);
            this.m_tlpTiming.TabIndex = 7;
            this.m_tlpTiming.Paint += new System.Windows.Forms.PaintEventHandler(this.tableLayoutPanel1_Paint);
            // 
            // m_lValidClockFreq
            // 
            this.m_lValidClockFreq.Anchor = System.Windows.Forms.AnchorStyles.Left;
            this.m_lValidClockFreq.AutoSize = true;
            this.m_lValidClockFreq.Location = new System.Drawing.Point(299, 39);
            this.m_lValidClockFreq.Name = "m_lValidClockFreq";
            this.m_lValidClockFreq.Size = new System.Drawing.Size(62, 13);
            this.m_lValidClockFreq.TabIndex = 7;
            this.m_lValidClockFreq.Text = "[1, 18] MHz";
            // 
            // m_lValidHeading
            // 
            this.m_lValidHeading.Anchor = System.Windows.Forms.AnchorStyles.Left;
            this.m_lValidHeading.AutoSize = true;
            this.m_lValidHeading.Font = new System.Drawing.Font("Microsoft Sans Serif", 8.25F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, ((byte)(0)));
            this.m_lValidHeading.Location = new System.Drawing.Point(299, 0);
            this.m_lValidHeading.Name = "m_lValidHeading";
            this.m_lValidHeading.Size = new System.Drawing.Size(79, 13);
            this.m_lValidHeading.TabIndex = 9;
            this.m_lValidHeading.Text = "Available rates:";
            // 
            // m_lValidScanRate
            // 
            this.m_lValidScanRate.Anchor = System.Windows.Forms.AnchorStyles.Left;
            this.m_lValidScanRate.AutoSize = true;
            this.m_lValidScanRate.Location = new System.Drawing.Point(299, 19);
            this.m_lValidScanRate.Name = "m_lValidScanRate";
            this.m_lValidScanRate.Size = new System.Drawing.Size(115, 13);
            this.m_lValidScanRate.TabIndex = 6;
            this.m_lValidScanRate.Text = "[12,000, 250,000] SPS";
            // 
            // m_lConversionTimeNum
            // 
            this.m_lConversionTimeNum.Anchor = System.Windows.Forms.AnchorStyles.Left;
            this.m_lConversionTimeNum.AutoSize = true;
            this.m_lConversionTimeNum.Font = new System.Drawing.Font("Microsoft Sans Serif", 8.25F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, ((byte)(0)));
            this.m_lConversionTimeNum.Location = new System.Drawing.Point(235, 52);
            this.m_lConversionTimeNum.Name = "m_lConversionTimeNum";
            this.m_lConversionTimeNum.Size = new System.Drawing.Size(39, 13);
            this.m_lConversionTimeNum.TabIndex = 10;
            this.m_lConversionTimeNum.Text = "123 ns";
            // 
            // m_lActualHeading
            // 
            this.m_lActualHeading.Anchor = System.Windows.Forms.AnchorStyles.Left;
            this.m_lActualHeading.AutoSize = true;
            this.m_lActualHeading.Font = new System.Drawing.Font("Microsoft Sans Serif", 8.25F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, ((byte)(0)));
            this.m_lActualHeading.Location = new System.Drawing.Point(235, 0);
            this.m_lActualHeading.Name = "m_lActualHeading";
            this.m_lActualHeading.Size = new System.Drawing.Size(55, 13);
            this.m_lActualHeading.TabIndex = 8;
            this.m_lActualHeading.Text = "Achieved:";
            // 
            // m_lConversionTime
            // 
            this.m_lConversionTime.Anchor = System.Windows.Forms.AnchorStyles.Left;
            this.m_lConversionTime.AutoSize = true;
            this.m_lConversionTime.Font = new System.Drawing.Font("Microsoft Sans Serif", 8.25F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, ((byte)(0)));
            this.m_lConversionTime.Location = new System.Drawing.Point(3, 52);
            this.m_lConversionTime.Name = "m_lConversionTime";
            this.m_lConversionTime.Size = new System.Drawing.Size(76, 13);
            this.m_lConversionTime.TabIndex = 11;
            this.m_lConversionTime.Text = "Scan duration:";
            // 
            // m_lActualClockFreq
            // 
            this.m_lActualClockFreq.Anchor = System.Windows.Forms.AnchorStyles.Left;
            this.m_lActualClockFreq.AutoSize = true;
            this.m_lActualClockFreq.Location = new System.Drawing.Point(235, 39);
            this.m_lActualClockFreq.Name = "m_lActualClockFreq";
            this.m_lActualClockFreq.Size = new System.Drawing.Size(44, 13);
            this.m_lActualClockFreq.TabIndex = 5;
            this.m_lActualClockFreq.Text = "18 MHz";
            // 
            // m_lActualSampleRate
            // 
            this.m_lActualSampleRate.Anchor = System.Windows.Forms.AnchorStyles.Left;
            this.m_lActualSampleRate.AutoSize = true;
            this.m_lActualSampleRate.Location = new System.Drawing.Point(235, 19);
            this.m_lActualSampleRate.Name = "m_lActualSampleRate";
            this.m_lActualSampleRate.Size = new System.Drawing.Size(58, 13);
            this.m_lActualSampleRate.TabIndex = 4;
            this.m_lActualSampleRate.Text = "2,500 SPS";
            // 
            // m_nudSampleRate
            // 
            this.m_nudSampleRate.Anchor = System.Windows.Forms.AnchorStyles.Left;
            this.m_nudSampleRate.Location = new System.Drawing.Point(135, 16);
            this.m_nudSampleRate.Margin = new System.Windows.Forms.Padding(3, 3, 19, 3);
            this.m_nudSampleRate.Maximum = new decimal(new int[] {
            1400000,
            0,
            0,
            0});
            this.m_nudSampleRate.Name = "m_nudSampleRate";
            this.m_nudSampleRate.Size = new System.Drawing.Size(78, 20);
            this.m_nudSampleRate.TabIndex = 2;
            this.m_nudSampleRate.Value = new decimal(new int[] {
            1400000,
            0,
            0,
            0});
            this.m_nudSampleRate.TextChanged += new System.EventHandler(this.nud_TextChanged);
            // 
            // label1
            // 
            this.label1.Anchor = System.Windows.Forms.AnchorStyles.Left;
            this.label1.AutoSize = true;
            this.label1.Location = new System.Drawing.Point(3, 19);
            this.label1.Name = "label1";
            this.label1.Size = new System.Drawing.Size(126, 13);
            this.label1.TabIndex = 12;
            this.label1.Text = "Free-run scan rate (SPS):";
            // 
            // label2
            // 
            this.label2.Anchor = System.Windows.Forms.AnchorStyles.Left;
            this.label2.AutoSize = true;
            this.label2.Location = new System.Drawing.Point(3, 39);
            this.label2.Name = "label2";
            this.label2.Size = new System.Drawing.Size(82, 13);
            this.label2.TabIndex = 13;
            this.label2.Text = "ADC clock rate:";
            // 
            // m_gbChannelConfiguration
            // 
            this.m_gbChannelConfiguration.Anchor = ((System.Windows.Forms.AnchorStyles)((((System.Windows.Forms.AnchorStyles.Top | System.Windows.Forms.AnchorStyles.Bottom) 
            | System.Windows.Forms.AnchorStyles.Left) 
            | System.Windows.Forms.AnchorStyles.Right)));
            this.m_gbChannelConfiguration.AutoSize = true;
            this.m_tlpSubTabConv.SetColumnSpan(this.m_gbChannelConfiguration, 3);
            this.m_gbChannelConfiguration.Controls.Add(this.tableLayoutPanel3);
            this.m_gbChannelConfiguration.Controls.Add(this.m_dgvChannels);
            this.m_gbChannelConfiguration.Location = new System.Drawing.Point(0, 395);
            this.m_gbChannelConfiguration.Margin = new System.Windows.Forms.Padding(0, 3, 0, 3);
            this.m_gbChannelConfiguration.MinimumSize = new System.Drawing.Size(1, 1);
            this.m_gbChannelConfiguration.Name = "m_gbChannelConfiguration";
            this.m_gbChannelConfiguration.Size = new System.Drawing.Size(640, 132);
            this.m_gbChannelConfiguration.TabIndex = 6;
            this.m_gbChannelConfiguration.TabStop = false;
            this.m_gbChannelConfiguration.Text = "Channels";
            // 
            // tableLayoutPanel3
            // 
            this.tableLayoutPanel3.AutoSize = true;
            this.tableLayoutPanel3.AutoSizeMode = System.Windows.Forms.AutoSizeMode.GrowAndShrink;
            this.tableLayoutPanel3.ColumnCount = 2;
            this.tableLayoutPanel3.ColumnStyles.Add(new System.Windows.Forms.ColumnStyle());
            this.tableLayoutPanel3.ColumnStyles.Add(new System.Windows.Forms.ColumnStyle());
            this.tableLayoutPanel3.Controls.Add(this.m_nudSequencedChannels, 1, 0);
            this.tableLayoutPanel3.Controls.Add(this.m_lSequencedChannels, 0, 0);
            this.tableLayoutPanel3.Dock = System.Windows.Forms.DockStyle.Top;
            this.tableLayoutPanel3.Location = new System.Drawing.Point(3, 16);
            this.tableLayoutPanel3.Name = "tableLayoutPanel3";
            this.tableLayoutPanel3.RowCount = 1;
            this.tableLayoutPanel3.RowStyles.Add(new System.Windows.Forms.RowStyle());
            this.tableLayoutPanel3.Size = new System.Drawing.Size(634, 26);
            this.tableLayoutPanel3.TabIndex = 7;
            // 
            // m_dgvChannels
            // 
            this.m_dgvChannels.AllowUserToAddRows = false;
            this.m_dgvChannels.AllowUserToDeleteRows = false;
            this.m_dgvChannels.AllowUserToResizeColumns = false;
            this.m_dgvChannels.AllowUserToResizeRows = false;
            this.m_dgvChannels.AutoSizeColumnsMode = System.Windows.Forms.DataGridViewAutoSizeColumnsMode.Fill;
            this.m_dgvChannels.AutoSizeRowsMode = System.Windows.Forms.DataGridViewAutoSizeRowsMode.AllCells;
            dataGridViewCellStyle1.Alignment = System.Windows.Forms.DataGridViewContentAlignment.MiddleCenter;
            dataGridViewCellStyle1.BackColor = System.Drawing.SystemColors.Control;
            dataGridViewCellStyle1.Font = new System.Drawing.Font("Microsoft Sans Serif", 7.8F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, ((byte)(0)));
            dataGridViewCellStyle1.ForeColor = System.Drawing.SystemColors.WindowText;
            dataGridViewCellStyle1.SelectionBackColor = System.Drawing.SystemColors.Highlight;
            dataGridViewCellStyle1.SelectionForeColor = System.Drawing.SystemColors.HighlightText;
            dataGridViewCellStyle1.WrapMode = System.Windows.Forms.DataGridViewTriState.True;
            this.m_dgvChannels.ColumnHeadersDefaultCellStyle = dataGridViewCellStyle1;
            this.m_dgvChannels.ColumnHeadersHeightSizeMode = System.Windows.Forms.DataGridViewColumnHeadersHeightSizeMode.AutoSize;
            this.m_dgvChannels.Columns.AddRange(new System.Windows.Forms.DataGridViewColumn[] {
            this.m_dgvcChannel,
            this.m_dgvcEnable,
            this.m_dgvcResolution,
            this.m_dgvcInputMode,
            this.m_dgvcAverage,
            this.m_dgvcAcqTime,
            this.m_dgvcActualAcq,
            this.m_dgvcMaxInResist,
            this.m_dgvcLimitInterrupt,
            this.m_dgvcSaturationInterrupt});
            this.m_dgvChannels.Dock = System.Windows.Forms.DockStyle.Bottom;
            this.m_dgvChannels.EditMode = System.Windows.Forms.DataGridViewEditMode.EditOnEnter;
            this.m_dgvChannels.Location = new System.Drawing.Point(3, 42);
            this.m_dgvChannels.Name = "m_dgvChannels";
            dataGridViewCellStyle4.Alignment = System.Windows.Forms.DataGridViewContentAlignment.MiddleCenter;
            dataGridViewCellStyle4.BackColor = System.Drawing.SystemColors.Control;
            dataGridViewCellStyle4.Font = new System.Drawing.Font("Microsoft Sans Serif", 7.8F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, ((byte)(0)));
            dataGridViewCellStyle4.ForeColor = System.Drawing.SystemColors.WindowText;
            dataGridViewCellStyle4.SelectionBackColor = System.Drawing.SystemColors.Highlight;
            dataGridViewCellStyle4.SelectionForeColor = System.Drawing.SystemColors.HighlightText;
            dataGridViewCellStyle4.WrapMode = System.Windows.Forms.DataGridViewTriState.True;
            this.m_dgvChannels.RowHeadersDefaultCellStyle = dataGridViewCellStyle4;
            this.m_dgvChannels.RowHeadersVisible = false;
            this.m_dgvChannels.ScrollBars = System.Windows.Forms.ScrollBars.None;
            this.m_dgvChannels.Size = new System.Drawing.Size(634, 87);
            this.m_dgvChannels.TabIndex = 2;
            this.m_dgvChannels.CellClick += new System.Windows.Forms.DataGridViewCellEventHandler(this.m_dgvChannels_CellClick);
            this.m_dgvChannels.CellValueChanged += new System.Windows.Forms.DataGridViewCellEventHandler(this.dataGridView1_CellContentClick);
            this.m_dgvChannels.CurrentCellDirtyStateChanged += new System.EventHandler(this.dgv_ElementDirty);
            this.m_dgvChannels.DataError += new System.Windows.Forms.DataGridViewDataErrorEventHandler(this.m_dgvChannelConfigs_DataError);
            this.m_dgvChannels.KeyDown += new System.Windows.Forms.KeyEventHandler(this.m_dgvChannels_KeyDown);
            this.m_dgvChannels.KeyPress += new System.Windows.Forms.KeyPressEventHandler(this.m_dgvChannels_KeyPress);
            // 
            // m_dgvcChannel
            // 
            this.m_dgvcChannel.AutoSizeMode = System.Windows.Forms.DataGridViewAutoSizeColumnMode.None;
            this.m_dgvcChannel.FillWeight = 25F;
            this.m_dgvcChannel.HeaderText = "Ch.";
            this.m_dgvcChannel.MinimumWidth = 35;
            this.m_dgvcChannel.Name = "m_dgvcChannel";
            this.m_dgvcChannel.ReadOnly = true;
            this.m_dgvcChannel.Resizable = System.Windows.Forms.DataGridViewTriState.False;
            this.m_dgvcChannel.SortMode = System.Windows.Forms.DataGridViewColumnSortMode.NotSortable;
            this.m_dgvcChannel.ToolTipText = global::Scan_ADC_v1_30.View.cytooltips.channelNumberToolTip;
            this.m_dgvcChannel.Width = 35;
            // 
            // m_dgvcEnable
            // 
            this.m_dgvcEnable.AutoSizeMode = System.Windows.Forms.DataGridViewAutoSizeColumnMode.None;
            this.m_dgvcEnable.FillWeight = 60F;
            this.m_dgvcEnable.HeaderText = "En";
            this.m_dgvcEnable.MinimumWidth = 30;
            this.m_dgvcEnable.Name = "m_dgvcEnable";
            this.m_dgvcEnable.Resizable = System.Windows.Forms.DataGridViewTriState.False;
            this.m_dgvcEnable.ToolTipText = global::Scan_ADC_v1_30.View.cytooltips.enableChannelToolTip;
            this.m_dgvcEnable.Width = 30;
            // 
            // m_dgvcResolution
            // 
            this.m_dgvcResolution.AutoSizeMode = System.Windows.Forms.DataGridViewAutoSizeColumnMode.Fill;
            this.m_dgvcResolution.DisplayStyle = System.Windows.Forms.DataGridViewComboBoxDisplayStyle.ComboBox;
            this.m_dgvcResolution.HeaderText = "Resolution";
            this.m_dgvcResolution.MinimumWidth = 100;
            this.m_dgvcResolution.Name = "m_dgvcResolution";
            this.m_dgvcResolution.Resizable = System.Windows.Forms.DataGridViewTriState.False;
            this.m_dgvcResolution.ToolTipText = global::Scan_ADC_v1_30.View.cytooltips.channelResolutionToolTip;
            // 
            // m_dgvcInputMode
            // 
            this.m_dgvcInputMode.AutoSizeMode = System.Windows.Forms.DataGridViewAutoSizeColumnMode.Fill;
            this.m_dgvcInputMode.FillWeight = 200F;
            this.m_dgvcInputMode.HeaderText = "Input mode";
            this.m_dgvcInputMode.MinimumWidth = 65;
            this.m_dgvcInputMode.Name = "m_dgvcInputMode";
            this.m_dgvcInputMode.Resizable = System.Windows.Forms.DataGridViewTriState.False;
            this.m_dgvcInputMode.ToolTipText = global::Scan_ADC_v1_30.View.cytooltips.channelInputModeToolTip;
            // 
            // m_dgvcAverage
            // 
            this.m_dgvcAverage.AutoSizeMode = System.Windows.Forms.DataGridViewAutoSizeColumnMode.None;
            this.m_dgvcAverage.FillWeight = 10F;
            this.m_dgvcAverage.HeaderText = "Avg";
            this.m_dgvcAverage.MinimumWidth = 33;
            this.m_dgvcAverage.Name = "m_dgvcAverage";
            this.m_dgvcAverage.Resizable = System.Windows.Forms.DataGridViewTriState.False;
            this.m_dgvcAverage.ToolTipText = global::Scan_ADC_v1_30.View.cytooltips.channelAveragingToolTip;
            this.m_dgvcAverage.Width = 33;
            // 
            // m_dgvcAcqTime
            // 
            this.m_dgvcAcqTime.AutoSizeMode = System.Windows.Forms.DataGridViewAutoSizeColumnMode.Fill;
            dataGridViewCellStyle2.Format = "N2";
            dataGridViewCellStyle2.NullValue = null;
            dataGridViewCellStyle2.WrapMode = System.Windows.Forms.DataGridViewTriState.False;
            this.m_dgvcAcqTime.DefaultCellStyle = dataGridViewCellStyle2;
            this.m_dgvcAcqTime.HeaderText = "Minimum acq. time (ns)";
            this.m_dgvcAcqTime.MinimumWidth = 60;
            this.m_dgvcAcqTime.Name = "m_dgvcAcqTime";
            this.m_dgvcAcqTime.Resizable = System.Windows.Forms.DataGridViewTriState.False;
            this.m_dgvcAcqTime.SortMode = System.Windows.Forms.DataGridViewColumnSortMode.NotSortable;
            this.m_dgvcAcqTime.ToolTipText = global::Scan_ADC_v1_30.View.cytooltips.minAcqTimeToolTip;
            // 
            // m_dgvcActualAcq
            // 
            this.m_dgvcActualAcq.AutoSizeMode = System.Windows.Forms.DataGridViewAutoSizeColumnMode.Fill;
            dataGridViewCellStyle3.BackColor = System.Drawing.Color.FromArgb(((int)(((byte)(224)))), ((int)(((byte)(224)))), ((int)(((byte)(224)))));
            this.m_dgvcActualAcq.DefaultCellStyle = dataGridViewCellStyle3;
            this.m_dgvcActualAcq.HeaderText = "Achieved acq. time (ns)";
            this.m_dgvcActualAcq.MinimumWidth = 60;
            this.m_dgvcActualAcq.Name = "m_dgvcActualAcq";
            this.m_dgvcActualAcq.ReadOnly = true;
            this.m_dgvcActualAcq.Resizable = System.Windows.Forms.DataGridViewTriState.False;
            this.m_dgvcActualAcq.SortMode = System.Windows.Forms.DataGridViewColumnSortMode.NotSortable;
            this.m_dgvcActualAcq.ToolTipText = global::Scan_ADC_v1_30.View.cytooltips.actAcqTimeToolTip;
            // 
            // m_dgvcMaxInResist
            // 
            this.m_dgvcMaxInResist.AutoSizeMode = System.Windows.Forms.DataGridViewAutoSizeColumnMode.Fill;
            this.m_dgvcMaxInResist.HeaderText = "Maximum source resistance (ohm)";
            this.m_dgvcMaxInResist.MinimumWidth = 60;
            this.m_dgvcMaxInResist.Name = "m_dgvcMaxInResist";
            this.m_dgvcMaxInResist.ReadOnly = true;
            this.m_dgvcMaxInResist.Resizable = System.Windows.Forms.DataGridViewTriState.True;
            this.m_dgvcMaxInResist.SortMode = System.Windows.Forms.DataGridViewColumnSortMode.NotSortable;
            this.m_dgvcMaxInResist.ToolTipText = global::Scan_ADC_v1_30.View.cytooltips.maxInputResistanceToolTip;
            this.m_dgvcMaxInResist.Visible = false;
            // 
            // m_dgvcLimitInterrupt
            // 
            this.m_dgvcLimitInterrupt.AutoSizeMode = System.Windows.Forms.DataGridViewAutoSizeColumnMode.Fill;
            this.m_dgvcLimitInterrupt.FillWeight = 75F;
            this.m_dgvcLimitInterrupt.HeaderText = "Limit interrupt";
            this.m_dgvcLimitInterrupt.MinimumWidth = 50;
            this.m_dgvcLimitInterrupt.Name = "m_dgvcLimitInterrupt";
            this.m_dgvcLimitInterrupt.Resizable = System.Windows.Forms.DataGridViewTriState.False;
            this.m_dgvcLimitInterrupt.ToolTipText = global::Scan_ADC_v1_30.View.cytooltips.channelUseLimitIntToolTip;
            // 
            // m_dgvcSaturationInterrupt
            // 
            this.m_dgvcSaturationInterrupt.AutoSizeMode = System.Windows.Forms.DataGridViewAutoSizeColumnMode.Fill;
            this.m_dgvcSaturationInterrupt.FillWeight = 75F;
            this.m_dgvcSaturationInterrupt.HeaderText = "Sat. interrupt";
            this.m_dgvcSaturationInterrupt.MinimumWidth = 50;
            this.m_dgvcSaturationInterrupt.Name = "m_dgvcSaturationInterrupt";
            this.m_dgvcSaturationInterrupt.Resizable = System.Windows.Forms.DataGridViewTriState.False;
            this.m_dgvcSaturationInterrupt.ToolTipText = global::Scan_ADC_v1_30.View.cytooltips.channelUseSaturationIntToolTip;
            // 
            // m_gbSampleMode
            // 
            this.m_gbSampleMode.Anchor = ((System.Windows.Forms.AnchorStyles)((((System.Windows.Forms.AnchorStyles.Top | System.Windows.Forms.AnchorStyles.Bottom) 
            | System.Windows.Forms.AnchorStyles.Left) 
            | System.Windows.Forms.AnchorStyles.Right)));
            this.m_gbSampleMode.AutoSize = true;
            this.m_gbSampleMode.AutoSizeMode = System.Windows.Forms.AutoSizeMode.GrowAndShrink;
            this.m_gbSampleMode.Controls.Add(this.m_cbUseSoc);
            this.m_gbSampleMode.Controls.Add(this.m_rbOneShot);
            this.m_gbSampleMode.Controls.Add(this.m_rbFreeRunning);
            this.m_gbSampleMode.Location = new System.Drawing.Point(524, 3);
            this.m_gbSampleMode.Margin = new System.Windows.Forms.Padding(3, 3, 0, 3);
            this.m_gbSampleMode.MinimumSize = new System.Drawing.Size(1, 1);
            this.m_gbSampleMode.Name = "m_gbSampleMode";
            this.m_gbSampleMode.Size = new System.Drawing.Size(116, 104);
            this.m_gbSampleMode.TabIndex = 2;
            this.m_gbSampleMode.TabStop = false;
            this.m_gbSampleMode.Text = "Sample Mode";
            // 
            // m_gbInputRange
            // 
            this.m_gbInputRange.Anchor = ((System.Windows.Forms.AnchorStyles)((System.Windows.Forms.AnchorStyles.Left | System.Windows.Forms.AnchorStyles.Right)));
            this.m_gbInputRange.AutoSize = true;
            this.m_gbInputRange.AutoSizeMode = System.Windows.Forms.AutoSizeMode.GrowAndShrink;
            this.m_tlpSubTabConv.SetColumnSpan(this.m_gbInputRange, 3);
            this.m_gbInputRange.Controls.Add(this.tableLayoutPanel2);
            this.m_gbInputRange.Location = new System.Drawing.Point(0, 113);
            this.m_gbInputRange.Margin = new System.Windows.Forms.Padding(0, 3, 0, 3);
            this.m_gbInputRange.MinimumSize = new System.Drawing.Size(1, 1);
            this.m_gbInputRange.Name = "m_gbInputRange";
            this.m_gbInputRange.Size = new System.Drawing.Size(640, 96);
            this.m_gbInputRange.TabIndex = 3;
            this.m_gbInputRange.TabStop = false;
            this.m_gbInputRange.Text = "Input Range";
            // 
            // tableLayoutPanel2
            // 
            this.tableLayoutPanel2.AutoSize = true;
            this.tableLayoutPanel2.AutoSizeMode = System.Windows.Forms.AutoSizeMode.GrowAndShrink;
            this.tableLayoutPanel2.ColumnCount = 6;
            this.tableLayoutPanel2.ColumnStyles.Add(new System.Windows.Forms.ColumnStyle());
            this.tableLayoutPanel2.ColumnStyles.Add(new System.Windows.Forms.ColumnStyle());
            this.tableLayoutPanel2.ColumnStyles.Add(new System.Windows.Forms.ColumnStyle(System.Windows.Forms.SizeType.Absolute, 60F));
            this.tableLayoutPanel2.ColumnStyles.Add(new System.Windows.Forms.ColumnStyle());
            this.tableLayoutPanel2.ColumnStyles.Add(new System.Windows.Forms.ColumnStyle());
            this.tableLayoutPanel2.ColumnStyles.Add(new System.Windows.Forms.ColumnStyle(System.Windows.Forms.SizeType.Absolute, 180F));
            this.tableLayoutPanel2.Controls.Add(this.m_lSEVoltRange, 5, 2);
            this.tableLayoutPanel2.Controls.Add(this.m_lVref, 0, 0);
            this.tableLayoutPanel2.Controls.Add(this.m_lSERangeRow, 3, 2);
            this.tableLayoutPanel2.Controls.Add(this.m_cbVrefBypass, 1, 1);
            this.tableLayoutPanel2.Controls.Add(this.m_lSECodeRange, 4, 2);
            this.tableLayoutPanel2.Controls.Add(this.m_lDiffRangeRow, 3, 1);
            this.tableLayoutPanel2.Controls.Add(this.m_cmbVrefSource, 1, 0);
            this.tableLayoutPanel2.Controls.Add(this.m_cmbVnegSource, 1, 2);
            this.tableLayoutPanel2.Controls.Add(this.m_lVneg, 0, 2);
            this.tableLayoutPanel2.Controls.Add(this.m_lDiffVoltRange, 5, 1);
            this.tableLayoutPanel2.Controls.Add(this.m_lDiffCodeRange, 4, 1);
            this.tableLayoutPanel2.Controls.Add(this.m_lCodeRangeHeading, 4, 0);
            this.tableLayoutPanel2.Controls.Add(this.m_lVoltRangeHeading, 5, 0);
            this.tableLayoutPanel2.Controls.Add(this.m_pVrefVoltage, 2, 0);
            this.tableLayoutPanel2.Controls.Add(this.m_lVrefErr, 3, 0);
            this.tableLayoutPanel2.Dock = System.Windows.Forms.DockStyle.Fill;
            this.tableLayoutPanel2.Location = new System.Drawing.Point(3, 16);
            this.tableLayoutPanel2.Name = "tableLayoutPanel2";
            this.tableLayoutPanel2.RowCount = 3;
            this.tableLayoutPanel2.RowStyles.Add(new System.Windows.Forms.RowStyle());
            this.tableLayoutPanel2.RowStyles.Add(new System.Windows.Forms.RowStyle());
            this.tableLayoutPanel2.RowStyles.Add(new System.Windows.Forms.RowStyle());
            this.tableLayoutPanel2.Size = new System.Drawing.Size(634, 77);
            this.tableLayoutPanel2.TabIndex = 19;
            // 
            // m_lSEVoltRange
            // 
            this.m_lSEVoltRange.Anchor = System.Windows.Forms.AnchorStyles.Left;
            this.m_lSEVoltRange.AutoSize = true;
            this.m_lSEVoltRange.Location = new System.Drawing.Point(452, 57);
            this.m_lSEVoltRange.Name = "m_lSEVoltRange";
            this.m_lSEVoltRange.Size = new System.Drawing.Size(119, 13);
            this.m_lSEVoltRange.TabIndex = 13;
            this.m_lSEVoltRange.Text = "Vneg-Vref to Vneg+Vref";
            // 
            // m_lVref
            // 
            this.m_lVref.Anchor = System.Windows.Forms.AnchorStyles.Left;
            this.m_lVref.AutoSize = true;
            this.m_lVref.Location = new System.Drawing.Point(3, 7);
            this.m_lVref.Name = "m_lVref";
            this.m_lVref.Size = new System.Drawing.Size(60, 13);
            this.m_lVref.TabIndex = 0;
            this.m_lVref.Text = "Vref select:";
            // 
            // m_lSERangeRow
            // 
            this.m_lSERangeRow.Anchor = System.Windows.Forms.AnchorStyles.Left;
            this.m_lSERangeRow.AutoSize = true;
            this.m_lSERangeRow.Font = new System.Drawing.Font("Microsoft Sans Serif", 8.25F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, ((byte)(0)));
            this.m_lSERangeRow.Location = new System.Drawing.Point(318, 57);
            this.m_lSERangeRow.Name = "m_lSERangeRow";
            this.m_lSERangeRow.Size = new System.Drawing.Size(29, 13);
            this.m_lSERangeRow.TabIndex = 17;
            this.m_lSERangeRow.Text = "S/E:";
            // 
            // m_lSECodeRange
            // 
            this.m_lSECodeRange.Anchor = System.Windows.Forms.AnchorStyles.Left;
            this.m_lSECodeRange.AutoSize = true;
            this.m_lSECodeRange.Location = new System.Drawing.Point(353, 57);
            this.m_lSECodeRange.Name = "m_lSECodeRange";
            this.m_lSECodeRange.Size = new System.Drawing.Size(49, 13);
            this.m_lSECodeRange.TabIndex = 11;
            this.m_lSECodeRange.Text = "[0, 4095]";
            // 
            // m_lDiffRangeRow
            // 
            this.m_lDiffRangeRow.Anchor = System.Windows.Forms.AnchorStyles.Left;
            this.m_lDiffRangeRow.AutoSize = true;
            this.m_lDiffRangeRow.Font = new System.Drawing.Font("Microsoft Sans Serif", 8.25F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, ((byte)(0)));
            this.m_lDiffRangeRow.Location = new System.Drawing.Point(318, 32);
            this.m_lDiffRangeRow.Name = "m_lDiffRangeRow";
            this.m_lDiffRangeRow.Size = new System.Drawing.Size(29, 13);
            this.m_lDiffRangeRow.TabIndex = 16;
            this.m_lDiffRangeRow.Text = "Diff.:";
            // 
            // m_lVneg
            // 
            this.m_lVneg.Anchor = System.Windows.Forms.AnchorStyles.Left;
            this.m_lVneg.AutoSize = true;
            this.m_lVneg.Location = new System.Drawing.Point(3, 57);
            this.m_lVneg.Name = "m_lVneg";
            this.m_lVneg.Size = new System.Drawing.Size(72, 13);
            this.m_lVneg.TabIndex = 3;
            this.m_lVneg.Text = "Vneg for S/E:";
            // 
            // m_lDiffVoltRange
            // 
            this.m_lDiffVoltRange.Anchor = System.Windows.Forms.AnchorStyles.Left;
            this.m_lDiffVoltRange.AutoSize = true;
            this.m_lDiffVoltRange.Location = new System.Drawing.Point(452, 32);
            this.m_lDiffVoltRange.Name = "m_lDiffVoltRange";
            this.m_lDiffVoltRange.Size = new System.Drawing.Size(86, 13);
            this.m_lDiffVoltRange.TabIndex = 12;
            this.m_lDiffVoltRange.Text = "[Vn - Vr, Vn + Vr]";
            // 
            // m_lDiffCodeRange
            // 
            this.m_lDiffCodeRange.Anchor = System.Windows.Forms.AnchorStyles.Left;
            this.m_lDiffCodeRange.AutoSize = true;
            this.m_lDiffCodeRange.Location = new System.Drawing.Point(353, 32);
            this.m_lDiffCodeRange.Name = "m_lDiffCodeRange";
            this.m_lDiffCodeRange.Size = new System.Drawing.Size(70, 13);
            this.m_lDiffCodeRange.TabIndex = 10;
            this.m_lDiffCodeRange.Text = "[-2048, 2047]";
            // 
            // m_lCodeRangeHeading
            // 
            this.m_lCodeRangeHeading.Anchor = System.Windows.Forms.AnchorStyles.Left;
            this.m_lCodeRangeHeading.AutoSize = true;
            this.m_lCodeRangeHeading.Font = new System.Drawing.Font("Microsoft Sans Serif", 8.25F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, ((byte)(0)));
            this.m_lCodeRangeHeading.Location = new System.Drawing.Point(353, 7);
            this.m_lCodeRangeHeading.Name = "m_lCodeRangeHeading";
            this.m_lCodeRangeHeading.Size = new System.Drawing.Size(93, 13);
            this.m_lCodeRangeHeading.TabIndex = 14;
            this.m_lCodeRangeHeading.Text = "12-bit code range:";
            // 
            // m_lVoltRangeHeading
            // 
            this.m_lVoltRangeHeading.Anchor = System.Windows.Forms.AnchorStyles.Left;
            this.m_lVoltRangeHeading.AutoSize = true;
            this.m_lVoltRangeHeading.Font = new System.Drawing.Font("Microsoft Sans Serif", 8.25F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, ((byte)(0)));
            this.m_lVoltRangeHeading.Location = new System.Drawing.Point(452, 7);
            this.m_lVoltRangeHeading.Name = "m_lVoltRangeHeading";
            this.m_lVoltRangeHeading.Size = new System.Drawing.Size(58, 13);
            this.m_lVoltRangeHeading.TabIndex = 15;
            this.m_lVoltRangeHeading.Text = "Volt range:";
            // 
            // m_pVrefVoltage
            // 
            this.m_pVrefVoltage.AutoSize = true;
            this.m_pVrefVoltage.Controls.Add(this.m_lVrefVoltage);
            this.m_pVrefVoltage.Controls.Add(this.m_nudVrefVoltage);
            this.m_pVrefVoltage.Dock = System.Windows.Forms.DockStyle.Fill;
            this.m_pVrefVoltage.Location = new System.Drawing.Point(258, 3);
            this.m_pVrefVoltage.MaximumSize = new System.Drawing.Size(81, 0);
            this.m_pVrefVoltage.Name = "m_pVrefVoltage";
            this.m_pVrefVoltage.Size = new System.Drawing.Size(54, 21);
            this.m_pVrefVoltage.TabIndex = 18;
            // 
            // m_lVrefVoltage
            // 
            this.m_lVrefVoltage.Anchor = System.Windows.Forms.AnchorStyles.Left;
            this.m_lVrefVoltage.AutoSize = true;
            this.m_lVrefVoltage.Location = new System.Drawing.Point(2, 1);
            this.m_lVrefVoltage.Name = "m_lVrefVoltage";
            this.m_lVrefVoltage.Size = new System.Drawing.Size(44, 13);
            this.m_lVrefVoltage.TabIndex = 3;
            this.m_lVrefVoltage.Text = "1.234 V";
            // 
            // m_lVrefErr
            // 
            this.m_lVrefErr.AutoSize = true;
            this.m_lVrefErr.Dock = System.Windows.Forms.DockStyle.Left;
            this.m_lVrefErr.Location = new System.Drawing.Point(318, 0);
            this.m_lVrefErr.Name = "m_lVrefErr";
            this.m_lVrefErr.Size = new System.Drawing.Size(10, 27);
            this.m_lVrefErr.TabIndex = 20;
            this.m_lVrefErr.Text = " ";
            // 
            // m_gbResultDataFormat
            // 
            this.m_gbResultDataFormat.Anchor = ((System.Windows.Forms.AnchorStyles)((((System.Windows.Forms.AnchorStyles.Top | System.Windows.Forms.AnchorStyles.Bottom) 
            | System.Windows.Forms.AnchorStyles.Left) 
            | System.Windows.Forms.AnchorStyles.Right)));
            this.m_gbResultDataFormat.AutoSize = true;
            this.m_gbResultDataFormat.AutoSizeMode = System.Windows.Forms.AutoSizeMode.GrowAndShrink;
            this.m_gbResultDataFormat.Controls.Add(this.m_tlpResultFormat);
            this.m_gbResultDataFormat.Location = new System.Drawing.Point(0, 215);
            this.m_gbResultDataFormat.Margin = new System.Windows.Forms.Padding(0, 3, 3, 3);
            this.m_gbResultDataFormat.MinimumSize = new System.Drawing.Size(267, 150);
            this.m_gbResultDataFormat.Name = "m_gbResultDataFormat";
            this.m_gbResultDataFormat.Size = new System.Drawing.Size(277, 174);
            this.m_gbResultDataFormat.TabIndex = 4;
            this.m_gbResultDataFormat.TabStop = false;
            this.m_gbResultDataFormat.Text = "Result Data Format";
            // 
            // m_tlpResultFormat
            // 
            this.m_tlpResultFormat.AutoSize = true;
            this.m_tlpResultFormat.AutoSizeMode = System.Windows.Forms.AutoSizeMode.GrowAndShrink;
            this.m_tlpResultFormat.ColumnCount = 2;
            this.m_tlpResultFormat.ColumnStyles.Add(new System.Windows.Forms.ColumnStyle());
            this.m_tlpResultFormat.ColumnStyles.Add(new System.Windows.Forms.ColumnStyle());
            this.m_tlpResultFormat.Controls.Add(this.m_cmbAlternateResolution, 1, 4);
            this.m_tlpResultFormat.Controls.Add(this.m_lDiffResultFormat, 0, 0);
            this.m_tlpResultFormat.Controls.Add(this.m_lAlternateResolution, 0, 4);
            this.m_tlpResultFormat.Controls.Add(this.m_cmbDiffResultFormat, 1, 0);
            this.m_tlpResultFormat.Controls.Add(this.m_cmbAveragingMode, 1, 3);
            this.m_tlpResultFormat.Controls.Add(this.m_lSEResultFormat, 0, 1);
            this.m_tlpResultFormat.Controls.Add(this.m_lAveragingMode, 0, 3);
            this.m_tlpResultFormat.Controls.Add(this.m_cmbSEResultFormat, 1, 1);
            this.m_tlpResultFormat.Controls.Add(this.m_cmbSamplesAveraged, 1, 2);
            this.m_tlpResultFormat.Controls.Add(this.m_lSamplesAveraged, 0, 2);
            this.m_tlpResultFormat.Dock = System.Windows.Forms.DockStyle.Fill;
            this.m_tlpResultFormat.Location = new System.Drawing.Point(3, 16);
            this.m_tlpResultFormat.Name = "m_tlpResultFormat";
            this.m_tlpResultFormat.RowCount = 6;
            this.m_tlpResultFormat.RowStyles.Add(new System.Windows.Forms.RowStyle());
            this.m_tlpResultFormat.RowStyles.Add(new System.Windows.Forms.RowStyle());
            this.m_tlpResultFormat.RowStyles.Add(new System.Windows.Forms.RowStyle());
            this.m_tlpResultFormat.RowStyles.Add(new System.Windows.Forms.RowStyle());
            this.m_tlpResultFormat.RowStyles.Add(new System.Windows.Forms.RowStyle());
            this.m_tlpResultFormat.RowStyles.Add(new System.Windows.Forms.RowStyle(System.Windows.Forms.SizeType.Absolute, 20F));
            this.m_tlpResultFormat.Size = new System.Drawing.Size(271, 155);
            this.m_tlpResultFormat.TabIndex = 7;
            // 
            // m_lDiffResultFormat
            // 
            this.m_lDiffResultFormat.Anchor = System.Windows.Forms.AnchorStyles.Left;
            this.m_lDiffResultFormat.AutoSize = true;
            this.m_lDiffResultFormat.Location = new System.Drawing.Point(3, 7);
            this.m_lDiffResultFormat.Name = "m_lDiffResultFormat";
            this.m_lDiffResultFormat.Size = new System.Drawing.Size(89, 13);
            this.m_lDiffResultFormat.TabIndex = 0;
            this.m_lDiffResultFormat.Text = "Diff. result format:";
            // 
            // m_lAlternateResolution
            // 
            this.m_lAlternateResolution.Anchor = System.Windows.Forms.AnchorStyles.Left;
            this.m_lAlternateResolution.AutoSize = true;
            this.m_lAlternateResolution.Location = new System.Drawing.Point(3, 115);
            this.m_lAlternateResolution.Name = "m_lAlternateResolution";
            this.m_lAlternateResolution.Size = new System.Drawing.Size(100, 13);
            this.m_lAlternateResolution.TabIndex = 11;
            this.m_lAlternateResolution.Text = "Alternate resolution:";
            // 
            // m_lSEResultFormat
            // 
            this.m_lSEResultFormat.Anchor = System.Windows.Forms.AnchorStyles.Left;
            this.m_lSEResultFormat.AutoSize = true;
            this.m_lSEResultFormat.Location = new System.Drawing.Point(3, 34);
            this.m_lSEResultFormat.Name = "m_lSEResultFormat";
            this.m_lSEResultFormat.Size = new System.Drawing.Size(89, 13);
            this.m_lSEResultFormat.TabIndex = 3;
            this.m_lSEResultFormat.Text = "S/E result format:";
            // 
            // m_lAveragingMode
            // 
            this.m_lAveragingMode.Anchor = System.Windows.Forms.AnchorStyles.Left;
            this.m_lAveragingMode.AutoSize = true;
            this.m_lAveragingMode.Location = new System.Drawing.Point(3, 88);
            this.m_lAveragingMode.Name = "m_lAveragingMode";
            this.m_lAveragingMode.Size = new System.Drawing.Size(87, 13);
            this.m_lAveragingMode.TabIndex = 9;
            this.m_lAveragingMode.Text = "Averaging mode:";
            // 
            // m_lSamplesAveraged
            // 
            this.m_lSamplesAveraged.Anchor = System.Windows.Forms.AnchorStyles.Left;
            this.m_lSamplesAveraged.AutoSize = true;
            this.m_lSamplesAveraged.Location = new System.Drawing.Point(3, 61);
            this.m_lSamplesAveraged.Name = "m_lSamplesAveraged";
            this.m_lSamplesAveraged.Size = new System.Drawing.Size(98, 13);
            this.m_lSamplesAveraged.TabIndex = 7;
            this.m_lSamplesAveraged.Text = "Samples averaged:";
            // 
            // m_gbInterruptLimits
            // 
            this.m_gbInterruptLimits.Anchor = ((System.Windows.Forms.AnchorStyles)((((System.Windows.Forms.AnchorStyles.Top | System.Windows.Forms.AnchorStyles.Bottom) 
            | System.Windows.Forms.AnchorStyles.Left) 
            | System.Windows.Forms.AnchorStyles.Right)));
            this.m_gbInterruptLimits.AutoSize = true;
            this.m_gbInterruptLimits.AutoSizeMode = System.Windows.Forms.AutoSizeMode.GrowAndShrink;
            this.m_tlpSubTabConv.SetColumnSpan(this.m_gbInterruptLimits, 2);
            this.m_gbInterruptLimits.Controls.Add(this.tableLayoutPanel1);
            this.m_gbInterruptLimits.Location = new System.Drawing.Point(283, 215);
            this.m_gbInterruptLimits.Margin = new System.Windows.Forms.Padding(3, 3, 0, 3);
            this.m_gbInterruptLimits.MinimumSize = new System.Drawing.Size(1, 1);
            this.m_gbInterruptLimits.Name = "m_gbInterruptLimits";
            this.m_gbInterruptLimits.Size = new System.Drawing.Size(357, 174);
            this.m_gbInterruptLimits.TabIndex = 5;
            this.m_gbInterruptLimits.TabStop = false;
            this.m_gbInterruptLimits.Text = "Interrupt Limits";
            // 
            // tableLayoutPanel1
            // 
            this.tableLayoutPanel1.AutoSize = true;
            this.tableLayoutPanel1.AutoSizeMode = System.Windows.Forms.AutoSizeMode.GrowAndShrink;
            this.tableLayoutPanel1.ColumnCount = 4;
            this.tableLayoutPanel1.ColumnStyles.Add(new System.Windows.Forms.ColumnStyle());
            this.tableLayoutPanel1.ColumnStyles.Add(new System.Windows.Forms.ColumnStyle(System.Windows.Forms.SizeType.Absolute, 100F));
            this.tableLayoutPanel1.ColumnStyles.Add(new System.Windows.Forms.ColumnStyle());
            this.tableLayoutPanel1.ColumnStyles.Add(new System.Windows.Forms.ColumnStyle(System.Windows.Forms.SizeType.Absolute, 100F));
            this.tableLayoutPanel1.Controls.Add(this.m_lCompareMode, 0, 0);
            this.tableLayoutPanel1.Controls.Add(this.m_lSELowLimitVolts, 1, 3);
            this.tableLayoutPanel1.Controls.Add(this.m_lLowLimit, 0, 1);
            this.tableLayoutPanel1.Controls.Add(this.m_lDiffLowLimitVolts, 1, 2);
            this.tableLayoutPanel1.Controls.Add(this.m_nudLowLimit, 1, 1);
            this.tableLayoutPanel1.Controls.Add(this.m_lHighLimit, 2, 1);
            this.tableLayoutPanel1.Controls.Add(this.m_lDiffLimitRow, 0, 2);
            this.tableLayoutPanel1.Controls.Add(this.m_lDiffHighLimitVolts, 3, 2);
            this.tableLayoutPanel1.Controls.Add(this.m_lSEHighLimitVolts, 3, 3);
            this.tableLayoutPanel1.Controls.Add(this.m_cmbCompareMode, 1, 0);
            this.tableLayoutPanel1.Controls.Add(this.m_nudHighLimit, 3, 1);
            this.tableLayoutPanel1.Controls.Add(this.m_lSELimitRow, 0, 3);
            this.tableLayoutPanel1.Controls.Add(this.m_lDiffAvgLimitRow, 0, 4);
            this.tableLayoutPanel1.Controls.Add(this.m_lSEAvgLimitRow, 0, 5);
            this.tableLayoutPanel1.Controls.Add(this.m_lDiffAvgLowLimitVolts, 1, 4);
            this.tableLayoutPanel1.Controls.Add(this.m_lSEAvgLowLimitVolts, 1, 5);
            this.tableLayoutPanel1.Controls.Add(this.m_lDiffAvgHighLimitVolts, 3, 4);
            this.tableLayoutPanel1.Controls.Add(this.m_lSEAvgHighLimitVolts, 3, 5);
            this.tableLayoutPanel1.Dock = System.Windows.Forms.DockStyle.Fill;
            this.tableLayoutPanel1.Location = new System.Drawing.Point(3, 16);
            this.tableLayoutPanel1.Name = "tableLayoutPanel1";
            this.tableLayoutPanel1.RowCount = 7;
            this.tableLayoutPanel1.RowStyles.Add(new System.Windows.Forms.RowStyle());
            this.tableLayoutPanel1.RowStyles.Add(new System.Windows.Forms.RowStyle());
            this.tableLayoutPanel1.RowStyles.Add(new System.Windows.Forms.RowStyle());
            this.tableLayoutPanel1.RowStyles.Add(new System.Windows.Forms.RowStyle());
            this.tableLayoutPanel1.RowStyles.Add(new System.Windows.Forms.RowStyle());
            this.tableLayoutPanel1.RowStyles.Add(new System.Windows.Forms.RowStyle());
            this.tableLayoutPanel1.RowStyles.Add(new System.Windows.Forms.RowStyle(System.Windows.Forms.SizeType.Absolute, 20F));
            this.tableLayoutPanel1.Size = new System.Drawing.Size(351, 155);
            this.tableLayoutPanel1.TabIndex = 8;
            // 
            // m_lCompareMode
            // 
            this.m_lCompareMode.Anchor = System.Windows.Forms.AnchorStyles.Left;
            this.m_lCompareMode.AutoSize = true;
            this.m_lCompareMode.Location = new System.Drawing.Point(3, 7);
            this.m_lCompareMode.Name = "m_lCompareMode";
            this.m_lCompareMode.Size = new System.Drawing.Size(81, 13);
            this.m_lCompareMode.TabIndex = 0;
            this.m_lCompareMode.Text = "Compare mode:";
            // 
            // m_lSELowLimitVolts
            // 
            this.m_lSELowLimitVolts.Anchor = System.Windows.Forms.AnchorStyles.Left;
            this.m_lSELowLimitVolts.AutoSize = true;
            this.m_lSELowLimitVolts.Font = new System.Drawing.Font("Microsoft Sans Serif", 8.25F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, ((byte)(0)));
            this.m_lSELowLimitVolts.Location = new System.Drawing.Point(87, 72);
            this.m_lSELowLimitVolts.Margin = new System.Windows.Forms.Padding(0);
            this.m_lSELowLimitVolts.Name = "m_lSELowLimitVolts";
            this.m_lSELowLimitVolts.Padding = new System.Windows.Forms.Padding(0, 3, 0, 3);
            this.m_lSELowLimitVolts.Size = new System.Drawing.Size(63, 19);
            this.m_lSELowLimitVolts.TabIndex = 9;
            this.m_lSELowLimitVolts.Text = "Vneg -0.0 V";
            // 
            // m_lLowLimit
            // 
            this.m_lLowLimit.Anchor = System.Windows.Forms.AnchorStyles.Left;
            this.m_lLowLimit.AutoSize = true;
            this.m_lLowLimit.Location = new System.Drawing.Point(3, 33);
            this.m_lLowLimit.Margin = new System.Windows.Forms.Padding(3, 0, 19, 0);
            this.m_lLowLimit.Name = "m_lLowLimit";
            this.m_lLowLimit.Size = new System.Drawing.Size(56, 13);
            this.m_lLowLimit.TabIndex = 3;
            this.m_lLowLimit.Text = "Low (hex):";
            // 
            // m_lDiffLowLimitVolts
            // 
            this.m_lDiffLowLimitVolts.Anchor = System.Windows.Forms.AnchorStyles.Left;
            this.m_lDiffLowLimitVolts.AutoSize = true;
            this.m_lDiffLowLimitVolts.Font = new System.Drawing.Font("Microsoft Sans Serif", 8.25F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, ((byte)(0)));
            this.m_lDiffLowLimitVolts.Location = new System.Drawing.Point(87, 53);
            this.m_lDiffLowLimitVolts.Margin = new System.Windows.Forms.Padding(0);
            this.m_lDiffLowLimitVolts.Name = "m_lDiffLowLimitVolts";
            this.m_lDiffLowLimitVolts.Padding = new System.Windows.Forms.Padding(0, 3, 0, 3);
            this.m_lDiffLowLimitVolts.Size = new System.Drawing.Size(13, 19);
            this.m_lDiffLowLimitVolts.TabIndex = 8;
            this.m_lDiffLowLimitVolts.Text = "0";
            // 
            // m_lHighLimit
            // 
            this.m_lHighLimit.Anchor = System.Windows.Forms.AnchorStyles.Right;
            this.m_lHighLimit.AutoSize = true;
            this.m_lHighLimit.Location = new System.Drawing.Point(190, 33);
            this.m_lHighLimit.Name = "m_lHighLimit";
            this.m_lHighLimit.Size = new System.Drawing.Size(58, 13);
            this.m_lHighLimit.TabIndex = 5;
            this.m_lHighLimit.Text = "High (hex):";
            // 
            // m_lDiffLimitRow
            // 
            this.m_lDiffLimitRow.Anchor = System.Windows.Forms.AnchorStyles.Left;
            this.m_lDiffLimitRow.AutoSize = true;
            this.m_lDiffLimitRow.Font = new System.Drawing.Font("Microsoft Sans Serif", 8.25F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, ((byte)(0)));
            this.m_lDiffLimitRow.Location = new System.Drawing.Point(0, 53);
            this.m_lDiffLimitRow.Margin = new System.Windows.Forms.Padding(0);
            this.m_lDiffLimitRow.Name = "m_lDiffLimitRow";
            this.m_lDiffLimitRow.Padding = new System.Windows.Forms.Padding(0, 3, 0, 3);
            this.m_lDiffLimitRow.Size = new System.Drawing.Size(74, 19);
            this.m_lDiffLimitRow.TabIndex = 6;
            this.m_lDiffLimitRow.Text = "Diff. value (V):";
            // 
            // m_lDiffHighLimitVolts
            // 
            this.m_lDiffHighLimitVolts.Anchor = System.Windows.Forms.AnchorStyles.Left;
            this.m_lDiffHighLimitVolts.AutoSize = true;
            this.m_lDiffHighLimitVolts.Font = new System.Drawing.Font("Microsoft Sans Serif", 8.25F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, ((byte)(0)));
            this.m_lDiffHighLimitVolts.Location = new System.Drawing.Point(251, 53);
            this.m_lDiffHighLimitVolts.Margin = new System.Windows.Forms.Padding(0);
            this.m_lDiffHighLimitVolts.Name = "m_lDiffHighLimitVolts";
            this.m_lDiffHighLimitVolts.Padding = new System.Windows.Forms.Padding(0, 3, 0, 3);
            this.m_lDiffHighLimitVolts.Size = new System.Drawing.Size(34, 19);
            this.m_lDiffHighLimitVolts.TabIndex = 10;
            this.m_lDiffHighLimitVolts.Text = "2.048";
            this.m_lDiffHighLimitVolts.Click += new System.EventHandler(this.m_lDiffHighLimitVolts_Click);
            // 
            // m_lSEHighLimitVolts
            // 
            this.m_lSEHighLimitVolts.Anchor = System.Windows.Forms.AnchorStyles.Left;
            this.m_lSEHighLimitVolts.AutoSize = true;
            this.m_lSEHighLimitVolts.Font = new System.Drawing.Font("Microsoft Sans Serif", 8.25F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, ((byte)(0)));
            this.m_lSEHighLimitVolts.Location = new System.Drawing.Point(251, 72);
            this.m_lSEHighLimitVolts.Margin = new System.Windows.Forms.Padding(0);
            this.m_lSEHighLimitVolts.Name = "m_lSEHighLimitVolts";
            this.m_lSEHighLimitVolts.Padding = new System.Windows.Forms.Padding(0, 3, 0, 3);
            this.m_lSEHighLimitVolts.Size = new System.Drawing.Size(78, 19);
            this.m_lSEHighLimitVolts.TabIndex = 11;
            this.m_lSEHighLimitVolts.Text = "Vneg +1.024 V";
            // 
            // m_lSELimitRow
            // 
            this.m_lSELimitRow.Anchor = System.Windows.Forms.AnchorStyles.Left;
            this.m_lSELimitRow.AutoSize = true;
            this.m_lSELimitRow.Font = new System.Drawing.Font("Microsoft Sans Serif", 8.25F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, ((byte)(0)));
            this.m_lSELimitRow.Location = new System.Drawing.Point(0, 72);
            this.m_lSELimitRow.Margin = new System.Windows.Forms.Padding(0);
            this.m_lSELimitRow.Name = "m_lSELimitRow";
            this.m_lSELimitRow.Padding = new System.Windows.Forms.Padding(0, 3, 0, 3);
            this.m_lSELimitRow.Size = new System.Drawing.Size(74, 19);
            this.m_lSELimitRow.TabIndex = 7;
            this.m_lSELimitRow.Text = "S/E value (V):";
            // 
            // m_lDiffAvgLimitRow
            // 
            this.m_lDiffAvgLimitRow.Anchor = System.Windows.Forms.AnchorStyles.Left;
            this.m_lDiffAvgLimitRow.AutoSize = true;
            this.m_lDiffAvgLimitRow.Location = new System.Drawing.Point(0, 91);
            this.m_lDiffAvgLimitRow.Margin = new System.Windows.Forms.Padding(0);
            this.m_lDiffAvgLimitRow.Name = "m_lDiffAvgLimitRow";
            this.m_lDiffAvgLimitRow.Padding = new System.Windows.Forms.Padding(0, 3, 0, 3);
            this.m_lDiffAvgLimitRow.Size = new System.Drawing.Size(66, 19);
            this.m_lDiffAvgLimitRow.TabIndex = 13;
            this.m_lDiffAvgLimitRow.Text = "Diff. avg (V):";
            // 
            // m_lSEAvgLimitRow
            // 
            this.m_lSEAvgLimitRow.AutoSize = true;
            this.m_lSEAvgLimitRow.Location = new System.Drawing.Point(0, 110);
            this.m_lSEAvgLimitRow.Margin = new System.Windows.Forms.Padding(0);
            this.m_lSEAvgLimitRow.Name = "m_lSEAvgLimitRow";
            this.m_lSEAvgLimitRow.Padding = new System.Windows.Forms.Padding(0, 3, 0, 3);
            this.m_lSEAvgLimitRow.Size = new System.Drawing.Size(66, 19);
            this.m_lSEAvgLimitRow.TabIndex = 14;
            this.m_lSEAvgLimitRow.Text = "S/E avg (V):";
            // 
            // m_lDiffAvgLowLimitVolts
            // 
            this.m_lDiffAvgLowLimitVolts.Anchor = System.Windows.Forms.AnchorStyles.Left;
            this.m_lDiffAvgLowLimitVolts.AutoSize = true;
            this.m_lDiffAvgLowLimitVolts.Location = new System.Drawing.Point(87, 91);
            this.m_lDiffAvgLowLimitVolts.Margin = new System.Windows.Forms.Padding(0);
            this.m_lDiffAvgLowLimitVolts.Name = "m_lDiffAvgLowLimitVolts";
            this.m_lDiffAvgLowLimitVolts.Padding = new System.Windows.Forms.Padding(0, 3, 0, 3);
            this.m_lDiffAvgLowLimitVolts.Size = new System.Drawing.Size(13, 19);
            this.m_lDiffAvgLowLimitVolts.TabIndex = 15;
            this.m_lDiffAvgLowLimitVolts.Text = "0";
            // 
            // m_lSEAvgLowLimitVolts
            // 
            this.m_lSEAvgLowLimitVolts.AutoSize = true;
            this.m_lSEAvgLowLimitVolts.Location = new System.Drawing.Point(87, 110);
            this.m_lSEAvgLowLimitVolts.Margin = new System.Windows.Forms.Padding(0);
            this.m_lSEAvgLowLimitVolts.Name = "m_lSEAvgLowLimitVolts";
            this.m_lSEAvgLowLimitVolts.Padding = new System.Windows.Forms.Padding(0, 3, 0, 3);
            this.m_lSEAvgLowLimitVolts.Size = new System.Drawing.Size(13, 19);
            this.m_lSEAvgLowLimitVolts.TabIndex = 16;
            this.m_lSEAvgLowLimitVolts.Text = "0";
            // 
            // m_lDiffAvgHighLimitVolts
            // 
            this.m_lDiffAvgHighLimitVolts.Anchor = System.Windows.Forms.AnchorStyles.Left;
            this.m_lDiffAvgHighLimitVolts.AutoSize = true;
            this.m_lDiffAvgHighLimitVolts.Location = new System.Drawing.Point(251, 91);
            this.m_lDiffAvgHighLimitVolts.Margin = new System.Windows.Forms.Padding(0);
            this.m_lDiffAvgHighLimitVolts.Name = "m_lDiffAvgHighLimitVolts";
            this.m_lDiffAvgHighLimitVolts.Padding = new System.Windows.Forms.Padding(0, 3, 0, 3);
            this.m_lDiffAvgHighLimitVolts.Size = new System.Drawing.Size(34, 19);
            this.m_lDiffAvgHighLimitVolts.TabIndex = 17;
            this.m_lDiffAvgHighLimitVolts.Text = "0.512";
            // 
            // m_lSEAvgHighLimitVolts
            // 
            this.m_lSEAvgHighLimitVolts.AutoSize = true;
            this.m_lSEAvgHighLimitVolts.Location = new System.Drawing.Point(251, 110);
            this.m_lSEAvgHighLimitVolts.Margin = new System.Windows.Forms.Padding(0);
            this.m_lSEAvgHighLimitVolts.Name = "m_lSEAvgHighLimitVolts";
            this.m_lSEAvgHighLimitVolts.Padding = new System.Windows.Forms.Padding(0, 3, 0, 3);
            this.m_lSEAvgHighLimitVolts.Size = new System.Drawing.Size(34, 19);
            this.m_lSEAvgHighLimitVolts.TabIndex = 18;
            this.m_lSEAvgHighLimitVolts.Text = "0.256";
            // 
            // CyConversionSubtab
            // 
            this.AutoScroll = true;
            this.Controls.Add(this.m_tlpSubTabConv);
            this.Margin = new System.Windows.Forms.Padding(0);
            this.MinimumSize = new System.Drawing.Size(1, 1);
            this.Name = "CyConversionSubtab";
            this.Size = new System.Drawing.Size(1000, 554);
            ((System.ComponentModel.ISupportInitialize)(this.m_nudLowLimit)).EndInit();
            ((System.ComponentModel.ISupportInitialize)(this.m_nudHighLimit)).EndInit();
            ((System.ComponentModel.ISupportInitialize)(this.m_nudVrefVoltage)).EndInit();
            ((System.ComponentModel.ISupportInitialize)(this.m_nudSequencedChannels)).EndInit();
            this.m_tlpSubTabConv.ResumeLayout(false);
            this.m_tlpSubTabConv.PerformLayout();
            this.m_gbTiming.ResumeLayout(false);
            this.m_gbTiming.PerformLayout();
            this.m_tlpTiming.ResumeLayout(false);
            this.m_tlpTiming.PerformLayout();
            ((System.ComponentModel.ISupportInitialize)(this.m_nudSampleRate)).EndInit();
            this.m_gbChannelConfiguration.ResumeLayout(false);
            this.m_gbChannelConfiguration.PerformLayout();
            this.tableLayoutPanel3.ResumeLayout(false);
            this.tableLayoutPanel3.PerformLayout();
            ((System.ComponentModel.ISupportInitialize)(this.m_dgvChannels)).EndInit();
            this.m_gbSampleMode.ResumeLayout(false);
            this.m_gbSampleMode.PerformLayout();
            this.m_gbInputRange.ResumeLayout(false);
            this.m_gbInputRange.PerformLayout();
            this.tableLayoutPanel2.ResumeLayout(false);
            this.tableLayoutPanel2.PerformLayout();
            this.m_pVrefVoltage.ResumeLayout(false);
            this.m_pVrefVoltage.PerformLayout();
            this.m_gbResultDataFormat.ResumeLayout(false);
            this.m_gbResultDataFormat.PerformLayout();
            this.m_tlpResultFormat.ResumeLayout(false);
            this.m_tlpResultFormat.PerformLayout();
            this.m_gbInterruptLimits.ResumeLayout(false);
            this.m_gbInterruptLimits.PerformLayout();
            this.tableLayoutPanel1.ResumeLayout(false);
            this.tableLayoutPanel1.PerformLayout();
            this.ResumeLayout(false);
            this.PerformLayout();

        }

        public void SetComponentsState()
        {

            this.m_nudSampleRate.Maximum = new decimal(new int[] {
                CyParamRanges.SAR_FREQ_MAX_HZ / CyParamRanges.SAR_SCAN_DURATION_MIN_CLKADC,
                0,
                0,
                0});

            if (m_params != null)
            {
                CyComboUtils.SetEnumDataSource<CyEAlternateResolution>(m_cmbAlternateResolution);
                CyComboUtils.SetEnumDataSource<CyEAveragingMode>(m_cmbAveragingMode);
                CyComboUtils.SetEnumDataSource<CyELimitComparisonMode>(m_cmbCompareMode);
                CyComboUtils.SetEnumDataSource<CyENumberFormat>(m_cmbDiffResultFormat);
                CyComboUtils.SetEnumDataSource<CyESamplesAveraged>(m_cmbSamplesAveraged);
                CyComboUtils.SetEnumDataSource<CyENumberFormat>(m_cmbSEResultFormat);
                CyComboUtils.SetEnumDataSource<CyEVnegSource>(m_cmbVnegSource);
                CyComboUtils.SetEnumDataSource<CyEVrefSource>(m_cmbVrefSource);

                SetDataGridViewState();
            }
        }

        private void SetDataGridViewState(){
            //Events hooked up using Designer-accessed Properties

            //Clear rows

            m_dgvChannels.Rows.Clear();

            //Add correct enumerations to comboboxes
            CyConfigModel config = m_params.GetConfig(m_configNumber);

            var column = (DataGridViewComboBoxColumn)
                m_dgvChannels.Columns[m_dgvcResolution.Index];
            string fullResDesc = CyEnumUtils.GetEnumDescription<CyEAllResolution>(
                CyEAllResolution.TWELVE_BIT);
            string altResDesc
                = CyEnumUtils.GetEnumDescription<CyEAlternateResolution>(
                    config.AlternateResolution);
            altResDesc += " (alt)";
            var dataSource = new List<CyDisplayValue<bool>>();
            dataSource.Add(new CyDisplayValue<bool>(fullResDesc, false));
            dataSource.Add(new CyDisplayValue<bool>(altResDesc, true));
            column.DisplayMember = "Display";
            column.ValueMember = "Value";
            column.DataSource = dataSource;

            // Make input mode lists with and without a filter option.
            var fullModeList = CyComboUtils.GetEnumMenuItems<CyEInputMode>();
            var nonfilterModeList = fullModeList
                .Where(m => m.Value != CyEInputMode.FILTER_CHAN).ToList();

            // Channels default to input modes without the filter option.
            column = (DataGridViewComboBoxColumn)
                m_dgvChannels.Columns[m_dgvcInputMode.Index];
            column.DisplayMember = "Display";
            column.ValueMember = "Value";
            column.DataSource = nonfilterModeList;

            //Add rows
            for (int curRowNum = 0; curRowNum < config.ChannelList.Count; curRowNum++)
            {
                object[] row = new object[m_dgvChannels.ColumnCount];
                m_dgvChannels.Rows.Add(row);
            }

            // Channel 0 can use the filter input mode if a filter is allowed or used.

            if ((this.m_params.IsFilterAllowed == true)
                || (CyModelUtils.AnyConfigUsesFilter(m_params) == true))
            {
                var inputMode0 = (DataGridViewComboBoxCell)
                    m_dgvChannels.Rows[0].Cells[m_dgvcInputMode.Index];
                inputMode0.DataSource = fullModeList;
            }

            ResizeDataGridView();
        }

        private void ResizeDataGridView()
        {

            CyConfigModel config = m_params.GetConfig(m_configNumber);
            m_dgvChannels.Height = (int)((m_dgvChannels.ColumnHeadersHeight)
                + (config.ChannelList.Count) * (m_dgvChannels.Rows[0].Height)
                + (m_dgvChannels.Margin.Bottom));
        }
        private void SetToolTips()
        {
            this.m_convToolTip.SetToolTip(this.m_nudSampleRate, Scan_ADC_v1_30.View.cytooltips.sampleRateToolTip);
            this.m_convToolTip.SetToolTip(this.m_rbFreeRunning, Scan_ADC_v1_30.View.cytooltips.freeRunningToolTip);
            this.m_convToolTip.SetToolTip(this.m_rbOneShot, Scan_ADC_v1_30.View.cytooltips.oneShotToolTip);
            this.m_convToolTip.SetToolTip(this.m_cbUseSoc, string.Format(Scan_ADC_v1_30.View.cytooltips.useSocToolTip, Scan_ADC_v1_30.View.cytooltips.commonTabName));            
            this.m_convToolTip.SetToolTip(this.m_lVref, Scan_ADC_v1_30.View.cytooltips.vrefSourceToolTip);
            this.m_convToolTip.SetToolTip(this.m_cmbVrefSource, Scan_ADC_v1_30.View.cytooltips.vrefSourceToolTip);
            this.m_convToolTip.SetToolTip(this.m_nudVrefVoltage, Scan_ADC_v1_30.View.cytooltips.vrefValueToolTip);
            this.m_convToolTip.SetToolTip(this.m_cbVrefBypass, Scan_ADC_v1_30.View.cytooltips.vrefBypassToolTip);
            this.m_convToolTip.SetToolTip(this.m_lVneg, Scan_ADC_v1_30.View.cytooltips.vnegSourceToolTip);
            this.m_convToolTip.SetToolTip(this.m_cmbVnegSource, Scan_ADC_v1_30.View.cytooltips.vnegSourceToolTip);
            this.m_convToolTip.SetToolTip(this.m_lDiffResultFormat, Scan_ADC_v1_30.View.cytooltips.diffResultFormatToolTip);
            this.m_convToolTip.SetToolTip(this.m_cmbDiffResultFormat, Scan_ADC_v1_30.View.cytooltips.diffResultFormatToolTip);
            this.m_convToolTip.SetToolTip(this.m_lSEResultFormat, Scan_ADC_v1_30.View.cytooltips.seResultFormatToolTip);
            this.m_convToolTip.SetToolTip(this.m_cmbSEResultFormat, Scan_ADC_v1_30.View.cytooltips.seResultFormatToolTip);
            this.m_convToolTip.SetToolTip(this.m_lSamplesAveraged, Scan_ADC_v1_30.View.cytooltips.samplesAvgdToolTip);
            this.m_convToolTip.SetToolTip(this.m_cmbSamplesAveraged, Scan_ADC_v1_30.View.cytooltips.samplesAvgdToolTip);
            this.m_convToolTip.SetToolTip(this.m_lAveragingMode, Scan_ADC_v1_30.View.cytooltips.averageModeToolTip);
            this.m_convToolTip.SetToolTip(this.m_cmbAveragingMode, Scan_ADC_v1_30.View.cytooltips.averageModeToolTip);
            this.m_convToolTip.SetToolTip(this.m_lAlternateResolution, Scan_ADC_v1_30.View.cytooltips.altResolutionToolTip);
            this.m_convToolTip.SetToolTip(this.m_cmbAlternateResolution, Scan_ADC_v1_30.View.cytooltips.altResolutionToolTip);
            this.m_convToolTip.SetToolTip(this.m_lCompareMode, Scan_ADC_v1_30.View.cytooltips.compareModeToolTip);
            this.m_convToolTip.SetToolTip(this.m_cmbCompareMode, Scan_ADC_v1_30.View.cytooltips.compareModeToolTip);
            this.m_convToolTip.SetToolTip(this.m_lLowLimit, Scan_ADC_v1_30.View.cytooltips.lowLimitToolTip);
            this.m_convToolTip.SetToolTip(this.m_nudLowLimit, Scan_ADC_v1_30.View.cytooltips.lowLimitToolTip);
            this.m_convToolTip.SetToolTip(this.m_lHighLimit, Scan_ADC_v1_30.View.cytooltips.highLimitToolTip);
            this.m_convToolTip.SetToolTip(this.m_nudHighLimit, Scan_ADC_v1_30.View.cytooltips.highLimitToolTip);
            this.m_convToolTip.SetToolTip(this.m_lSequencedChannels, Scan_ADC_v1_30.View.cytooltips.sequencedChannelsToolTip);
            this.m_convToolTip.SetToolTip(this.m_nudSequencedChannels, Scan_ADC_v1_30.View.cytooltips.sequencedChannelsToolTip);
        }

        public void UpdateUI()
        {
            m_blockParamUpdate = true;

            CyConfigModel config = m_params.GetConfig(m_configNumber);

            m_rbFreeRunning.Checked = config.FreeRunning;
            m_rbOneShot.Checked = !m_rbFreeRunning.Checked;
            m_cbUseSoc.Checked = config.UseSoc;
            m_cbVrefBypass.Checked = config.VrefBypass;
            m_cmbVrefSource.SelectedValue = config.VrefSource;

            UpdateVrefControls();
            m_cmbVnegSource.SelectedValue = config.VnegSource;

            m_cmbDiffResultFormat.SelectedValue = config.DiffResultFormat;
            m_cmbSEResultFormat.SelectedValue = config.SingleEndedResultFormat;
            m_cmbSamplesAveraged.SelectedValue = config.SamplesAveraged;
            m_cmbAveragingMode.SelectedValue = config.AveragingMode;
            m_cmbAlternateResolution.SelectedValue = config.AlternateResolution;

            m_cmbCompareMode.SelectedValue = config.CompareMode;
            SetNumUpDownValue(m_nudLowLimit, (decimal)config.LowLimit);
            SetNumUpDownValue(m_nudHighLimit, (decimal)config.HighLimit);
            SetNumUpDownValue(m_nudSequencedChannels, config.NumChannels);
            for (int chanNum = 0; chanNum < config.ChannelList.Count; chanNum++)
            {
                CyChannelModel tmpChanModel;
                try
                {
                    tmpChanModel = config.ChannelList[chanNum];
                }
                catch (Exception)
                {
                    tmpChanModel = new CyChannelModel(false, false,
                        CyEInputMode.DIFFERENTIAL_CHAN, false, 0.1, true, true);
                }

                m_dgvChannels[m_dgvcChannel.Index, chanNum].Value = chanNum.ToString();
                m_dgvChannels[m_dgvcEnable.Index, chanNum].Value = tmpChanModel.Enabled;
                m_dgvChannels[m_dgvcResolution.Index, chanNum].Value = tmpChanModel.UseAltResolution;
                m_dgvChannels[m_dgvcInputMode.Index, chanNum].Value = tmpChanModel.InputMode;
                m_dgvChannels[m_dgvcAverage.Index, chanNum].Value = tmpChanModel.UseAveraging;
                m_dgvChannels[m_dgvcAcqTime.Index, chanNum].Value = tmpChanModel.MinimumAcqTime;
                m_dgvChannels[m_dgvcActualAcq.Index, chanNum].Value = CalculateActualAcqTime_ns(chanNum);
                m_dgvChannels[m_dgvcMaxInResist.Index, chanNum].Value = CalculateMaxResist_ohm();
                m_dgvChannels[m_dgvcLimitInterrupt.Index, chanNum].Value = tmpChanModel.UseLimitInterrupt;
                m_dgvChannels[m_dgvcSaturationInterrupt.Index, chanNum].Value = tmpChanModel.UseSaturationInterrupt;

                m_dgvChannels[m_dgvcChannel.Index, chanNum].ToolTipText = global::Scan_ADC_v1_30.View.cytooltips.channelNumberToolTip;
                m_dgvChannels[m_dgvcEnable.Index, chanNum].ToolTipText = global::Scan_ADC_v1_30.View.cytooltips.enableChannelToolTip;
                m_dgvChannels[m_dgvcResolution.Index, chanNum].ToolTipText = global::Scan_ADC_v1_30.View.cytooltips.channelResolutionToolTip;
                m_dgvChannels[m_dgvcInputMode.Index, chanNum].ToolTipText = global::Scan_ADC_v1_30.View.cytooltips.channelInputModeToolTip;
                m_dgvChannels[m_dgvcAverage.Index, chanNum].ToolTipText = global::Scan_ADC_v1_30.View.cytooltips.channelAveragingToolTip;
                m_dgvChannels[m_dgvcAcqTime.Index, chanNum].ToolTipText = global::Scan_ADC_v1_30.View.cytooltips.minAcqTimeToolTip;
                m_dgvChannels[m_dgvcActualAcq.Index, chanNum].ToolTipText = global::Scan_ADC_v1_30.View.cytooltips.actAcqTimeToolTip;
                m_dgvChannels[m_dgvcMaxInResist.Index, chanNum].ToolTipText = global::Scan_ADC_v1_30.View.cytooltips.maxInputResistanceToolTip;
                m_dgvChannels[m_dgvcLimitInterrupt.Index, chanNum].ToolTipText = global::Scan_ADC_v1_30.View.cytooltips.channelUseLimitIntToolTip;
                m_dgvChannels[m_dgvcSaturationInterrupt.Index, chanNum].ToolTipText = global::Scan_ADC_v1_30.View.cytooltips.channelUseSaturationIntToolTip;
            }

            SetToolTips();
            UpdateGuiErrors();
            ResizeDataGridView();

            m_nudSampleRate.Enabled = config.FreeRunning;

            var scanUs = config.ActualScanUs;
            this.m_lConversionTimeNum.Text = scanUs==0 ? "---" : scanUs.ToString("N3") + " us";

            var sampleRate = config.ActualSampleRate;
            this.m_lActualSampleRate.Text = sampleRate==0 ? "---" : sampleRate.ToString("N0") + " SPS";

            UpdateAdcClockRateDisplay(config);
            UpdateScanRateDisplay(config);
            UpdateHexVoltageLabels();
            UpdateRangeLabels();

            m_blockParamUpdate = false;
        }

        private void UpdateScanRateDisplay(CyConfigModel config)
        {
            SetNumUpDownValue(m_nudSampleRate, (decimal)config.SampleRate);

            string achievableScanRates;

            achievableScanRates = string.Format("{0:N0} to {1:N0} SPS",
                config.MinScanRate,
                config.MaxScanRate);

            m_lValidScanRate.Text = achievableScanRates;
        }

        private void UpdateAdcClockRateDisplay(CyConfigModel config)
        {
            this.m_lActualClockFreq.Text = config.ActualAdcClockHz == 0
                ? "---"
                : CyModelUtils.ClockFreqMHzText(config.ActualAdcClockHz);

            m_lValidClockFreq.Text = CyModelUtils.ClockRangeMHzText(
                config.MinSarFrequency, config.MaxSarFrequency);
        }

        private void UpdateGuiErrors()
        {
            CyConfigModel config = m_params.GetConfig(this.ConfigNumber);
            string partNumber = CyCustomizer.ProjectPartNumber(m_params.InstQuery);
            string message;

            message = ((m_params.IsFilterAllowed == false)
                && (config.ChannelList[0].InputMode == CyEInputMode.FILTER_CHAN))
                ? string.Format(
                    global::Scan_ADC_v1_30.Controller.cydrcerrors.FilterNotSupportedNotice,
                    partNumber)
                    : string.Empty;
            m_dgvChannels[m_dgvcInputMode.Index, 0].ErrorText = message;

            /* Check each channel to see if it uses alt resolution and averaging,
             * which is not allowed. Also accumulate enable status. */
            bool anyChanEnabled = false;
            for (int chanNum = 0; chanNum < config.ChannelList.Count; chanNum++)
            {
                message = (CyGuiChecks.IsAltResAverage(config, chanNum))
                    ? global::Scan_ADC_v1_30.View.cyguierrors.AltResolutionAverage
                    : string.Empty;
                m_dgvChannels[m_dgvcChannel.Index, chanNum].ErrorText = message;
                anyChanEnabled = (anyChanEnabled
                               || CyGuiChecks.IsChannelEnabled(config, chanNum));
            }
            message = !anyChanEnabled
                ? global::Scan_ADC_v1_30.Controller.cydrcerrors.AllChannelsDisabled
                : string.Empty;
            m_errorProvider.SetError(m_nudSequencedChannels, message);

            var maxVref = CyVoltage.GetDesignVrefValue(m_params, CyEVrefSource.VREFSOURCE_VDDA);
            var minVref = CyParamRanges.MIN_VREF;
            message = config.VrefVoltage > maxVref
                    ? string.Format(Scan_ADC_v1_30.View.cyguierrors.VrefTooHigh, maxVref.ToString("N3"))
                    : config.VrefVoltage < minVref
                    ? string.Format(Scan_ADC_v1_30.View.cyguierrors.VrefTooLow, minVref.ToString("N3"))
                    : "";
            m_errorProvider.SetError(m_lVrefErr, message);

            if ((config.VrefSource == CyEVrefSource.VREFSOURCE_VDDA) && config.VrefBypass)
            {
                m_noteProvider.SetError(m_cbVrefBypass, Scan_ADC_v1_30.View.cyguierrors.VrefBypassNotice);
            }
            else
            {
                m_noteProvider.SetError(m_cbVrefBypass, "");
            }

            if ((config.VnegSource != CyEVnegSource.VNEGSOURCE_VREFSHORT && config.SingleEndedResultFormat == CyENumberFormat.UNSIGNED_FORMAT))
            {
                m_warningProvider.SetError(m_cmbSEResultFormat, Scan_ADC_v1_30.View.cyguierrors.VnegResultNotice);
            }
            else
            {
                m_warningProvider.SetError(m_cmbSEResultFormat, "");
            }

            if (CyGuiChecks.IsAverageOverflow(config))
            {
                m_warningProvider.SetError(m_cmbSamplesAveraged, Scan_ADC_v1_30.View.cyguierrors.AverageOverflowNotice);
            }
            else
            {
                m_warningProvider.SetError(m_cmbSamplesAveraged, "");
            }

            var convTimeNotice
                = CyModelUtils.InvalidExternalAdcClock(m_params)
                ? Scan_ADC_v1_30.View.cyguierrors.ExternalClockNotice
                : CyModelUtils.InvalidInternalAdcClock(m_params)
                ? Scan_ADC_v1_30.View.cyguierrors.InternalClockNotice
                : "";
            m_errorProvider.SetError(m_lConversionTimeNum, convTimeNotice);

            var adcClockNotice
                = CyModelUtils.AdcClockOutOfRange(m_params, this.ConfigNumber)
                ? string.Format(Scan_ADC_v1_30.View.cyguierrors.AdcClockOutOfRange,
                CyModelUtils.ClockFreqMHzText(config.ActualAdcClockHz),
                CyModelUtils.ClockRangeMHzText(config.MinSarFrequency, config.MaxSarFrequency))
                : "";
            m_errorProvider.SetError(m_lActualClockFreq, adcClockNotice);
        }

        private void UpdateVrefControls()
        {
            var displayValue
                        = (CyDisplayValue<CyEVrefSource>)m_cmbVrefSource.SelectedItem;

            if (displayValue != null)
            {
                /* If external, then user must supply Vref voltage to use in calculations.
                   Hide label, show nud.  Otherwise, hide nud, show label.   
                   Query for correct label to use. */
                double vrefAmt = m_params.GetConfig(ConfigNumber).VrefVoltage;

                if (   displayValue.Value == CyEVrefSource.VREFSOURCE_EXTERNAL
                    || displayValue.Value == CyEVrefSource.VREFSOURCE_DEVPIN)
                {
                    m_nudVrefVoltage.Visible = true;
                    m_lVrefVoltage.Visible = false;
                }
                else
                {
                    m_nudVrefVoltage.Visible = false;
                    m_lVrefVoltage.Visible = true;
                    vrefAmt = CyVoltage.GetDesignVrefValue(m_params, displayValue.Value);
                }
                var tmpUncheck = m_blockParamUpdate;
                m_blockParamUpdate = false;
                SetNumUpDownValue(m_nudVrefVoltage, (decimal)vrefAmt);
                m_blockParamUpdate = tmpUncheck;
                m_lVrefVoltage.Text = vrefAmt.ToString("N3") + " V";

            }
        }

        private void UpdateHexVoltageLabels()
        {
            CyConfigModel config = m_params.GetConfig(m_configNumber);
            //Single ended
            //Values to represent voltages not displayed here.
            double vLow, vHigh, vLowClip, vHighClip;

            //Values to get saved as text.
            double highVolt, lowVolt, highVoltAvg, lowVoltAvg;
            string highVoltString, lowVoltString;
            string lowPre = "";
            string highPre = "";
            ushort highCode = (ushort)config.HighLimit;
            ushort lowCode = (ushort)config.LowLimit;


            /* For modes besides Vneg = Vref, center code is assumed to = 0V.
               For Vneg = Vref, center code is = Vref. */
            if (config.VnegSource == CyEVnegSource.VNEGSOURCE_VREFSHORT)
            {
                vLow = 0;
                vHigh = 2 * config.VrefVoltage;
            } else
            {
                vLow = -config.VrefVoltage;
                vHigh = config.VrefVoltage;
            }

            //Signed
            if (config.SingleEndedResultFormat == CyENumberFormat.SIGNED_FORMAT)
            {
                var signLowCode = (short)lowCode;
                var signHighCode = (short)highCode;

                lowVolt = (vHigh + vLow) / 2 + ((vHigh - vLow) * (double)signLowCode) / 4096;
                highVolt = (vHigh + vLow) / 2 + ((vHigh - vLow) * (double)signHighCode) / 4096;
            }
            else //UNSIGNED
            {
                lowVolt = vLow + ((vHigh - vLow) * (double)lowCode) / 4096;
                highVolt = vLow + ((vHigh - vLow) * (double)highCode) / 4096;
            }

            /* Single-Ended label updates... */
            if (config.VnegSource == CyEVnegSource.VNEGSOURCE_VSSA_K 
             || config.VnegSource == CyEVnegSource.VNEGSOURCE_VREFSHORT)
            {
                vLowClip = Math.Max(0, vLow);
                vHighClip = Math.Min(vHigh, 5.5);
            }
            else //VNEGSOURCE_EXTERNAL
            {
                vLowClip = vLow;
                vHighClip = vHigh;

                lowPre =  "Vneg " + (lowVolt  > 0 ? "+" : "");
                highPre = "Vneg " + (highVolt > 0 ? "+" : "");
            }

            var avgDivider = 1;
            int sampAvgd = (int)CyModelUtils.AverageEnum2Long(config.SamplesAveraged);
            switch (config.AveragingMode)
            {
                case CyEAveragingMode.ACCUMULATE_AVG: //Sequential, Sum
                    if (sampAvgd > 16)
                    {
                        avgDivider = 16;
                    }
                    else
                    {
                        avgDivider = sampAvgd;
                    }
                    break;
                case CyEAveragingMode.INTERLEAVED_AVG: //Interleaved, Sum
                    avgDivider = sampAvgd;
                    break;
                case CyEAveragingMode.SEQUENTIAL_AVG: //Sequential, Fixed
                default:
                    avgDivider = 1;
                    break;
            }

            //Clip voltages
            lowVoltAvg = lowVolt / avgDivider;
            highVoltAvg = highVolt / avgDivider;
            lowVolt = Math.Min(vHighClip, Math.Max(vLowClip, lowVolt));
            highVolt = Math.Max(vLowClip, Math.Min(vHighClip, highVolt));
            lowVoltAvg = Math.Min(vHighClip, Math.Max(vLowClip, lowVoltAvg));
            highVoltAvg = Math.Max(vLowClip, Math.Min(vHighClip, highVoltAvg));
            
            //Convert to string for label
            lowVoltString = lowPre + lowVolt.ToString("#0.00 V");
            highVoltString = highPre + highVolt.ToString("#0.00 V");
            this.m_lSELowLimitVolts.Text = lowVoltString;
            this.m_lSEHighLimitVolts.Text = highVoltString;
            lowVoltString = lowPre + lowVoltAvg.ToString("#0.00 V");
            highVoltString = highPre + highVoltAvg.ToString("#0.00 V");
            this.m_lSEAvgLowLimitVolts.Text = lowVoltString;
            this.m_lSEAvgHighLimitVolts.Text = highVoltString;

            /* Differential labels */
            
            //Signed
            if (config.DiffResultFormat == CyENumberFormat.SIGNED_FORMAT)
            {
                vLow = -config.VrefVoltage;
                vHigh = config.VrefVoltage;
                var signLowCode = (short)lowCode;
                var signHighCode = (short)highCode;

                lowVolt = (vHigh + vLow) / 2 + ((vHigh - vLow) * (double)signLowCode) / 4096;
                highVolt = (vHigh + vLow) / 2 + ((vHigh - vLow) * (double)signHighCode) / 4096;
            }
            else //UNSIGNED
            {
                vLow = 0;
                vHigh = 2 * config.VrefVoltage;
                lowVolt = vLow + ((vHigh - vLow) * (double)lowCode) / 4096;
                highVolt = vLow + ((vHigh - vLow) * (double)highCode) / 4096;
            }

            vLowClip = vLow;
            vHighClip = vHigh;

            //Clip voltages
            lowVoltAvg = lowVolt / avgDivider;
            highVoltAvg = highVolt / avgDivider;
            lowVolt = Math.Min(vHighClip, Math.Max(vLowClip, lowVolt));
            highVolt = Math.Max(vLowClip, Math.Min(vHighClip, highVolt));
            lowVoltAvg = Math.Min(vHighClip, Math.Max(vLowClip, lowVoltAvg));
            highVoltAvg = Math.Max(vLowClip, Math.Min(vHighClip, highVoltAvg));

            //Convert to string for label
            lowVoltString = lowVolt.ToString("#0.00 V");
            highVoltString = highVolt.ToString("#0.00 V");
            this.m_lDiffLowLimitVolts.Text = lowVoltString;
            this.m_lDiffHighLimitVolts.Text = highVoltString;

            //Convert to string for label
            lowVoltString = lowVoltAvg.ToString("#0.00 V");
            highVoltString = highVoltAvg.ToString("#0.00 V");
            this.m_lDiffAvgLowLimitVolts.Text = lowVoltString;
            this.m_lDiffAvgHighLimitVolts.Text = highVoltString;
        }

        private void UpdateRangeLabels()
        {
            CyConfigModel configModel = m_params.GetConfig(m_configNumber);
            Dictionary<string, string> rangeLabels = CyModelUtils.ChannelRangeLabels(configModel);

            if(configModel.SingleEndedResultFormat == CyENumberFormat.SIGNED_FORMAT)
            { //-2048 to 2047
                m_lSECodeRange.Text = "0x800 to 0x7FF";
            }
            else //UNSIGNED_FORMAT
            { //0 to 4095
                if (configModel.VnegSource == CyEVnegSource.VNEGSOURCE_VSSA_K)
                {
                    m_lSECodeRange.Text = "0x800 to 0xFFF";
                }
                else
                {
                    m_lSECodeRange.Text = "0x000 to 0xFFF";
                }
            }
            if(configModel.DiffResultFormat == CyENumberFormat.SIGNED_FORMAT)
            { //-2048 to 2047
                m_lDiffCodeRange.Text = "0x800 to 0x7FF";
            }
            else //UNSIGNED_FORMAT
            { //0 to 4095
                m_lDiffCodeRange.Text = "0x000 to 0xFFF";
            }

            m_lSEVoltRange.Text = rangeLabels["seVoltRange"];
            m_lDiffVoltRange.Text = rangeLabels["diffVoltRange"];
        }

        private void cmb_SelectedIndexChanged(object sender, EventArgs e)
        {
            if (m_blockParamUpdate == false)
            {
                CyConfigModel config = m_params.GetConfig(m_configNumber);
                bool updateDataGridView = false;
                bool updateScanSchedule = false;

                if (sender == m_cmbAlternateResolution)
                {
                    var displayValue
                        = (CyDisplayValue<CyEAlternateResolution>)m_cmbAlternateResolution.SelectedItem;
                    if (displayValue != null)
                    {
                        config.AlternateResolution = displayValue.Value;
                    }
                    updateDataGridView = true;
                    updateScanSchedule = true;
                }
                else if (sender == m_cmbAveragingMode)
                {
                    var displayValue
                        = (CyDisplayValue<CyEAveragingMode>)m_cmbAveragingMode.SelectedItem;
                    if (displayValue != null)
                    {
                        config.AveragingMode = displayValue.Value;
                    }
                    updateScanSchedule = true;
                }
                else if (sender == m_cmbCompareMode)
                {
                    var displayValue
                        = (CyDisplayValue<CyELimitComparisonMode>)m_cmbCompareMode.SelectedItem;
                    if (displayValue != null)
                    {
                        config.CompareMode = displayValue.Value;
                    }
                }
                else if (sender == m_cmbDiffResultFormat)
                {
                    var displayValue
                        = (CyDisplayValue<CyENumberFormat>)m_cmbDiffResultFormat.SelectedItem;
                    if (displayValue != null)
                    {
                        config.DiffResultFormat = displayValue.Value;
                    }
                }
                else if (sender == m_cmbSamplesAveraged)
                {
                    var displayValue
                        = (CyDisplayValue<CyESamplesAveraged>)m_cmbSamplesAveraged.SelectedItem;
                    if (displayValue != null)
                    {
                        config.SamplesAveraged = displayValue.Value;
                    }
                    updateScanSchedule = true;
                }
                else if (sender == m_cmbSEResultFormat)
                {
                    var displayValue
                        = (CyDisplayValue<CyENumberFormat>)m_cmbSEResultFormat.SelectedItem;
                    if (displayValue != null)
                    {
                        config.SingleEndedResultFormat = displayValue.Value;
                    }
                }
                else if (sender == m_cmbVnegSource)
                {
                    var displayValue
                        = (CyDisplayValue<CyEVnegSource>)m_cmbVnegSource.SelectedItem;
                    if (displayValue != null)
                    {
                        config.VnegSource = displayValue.Value;
                    }
                }
                else if (sender == m_cmbVrefSource)
                {
                    var displayValue
                        = (CyDisplayValue<CyEVrefSource>)m_cmbVrefSource.SelectedItem;
                    
                    if (displayValue != null)
                    {
                        config.VrefSource = displayValue.Value;
                    }
                }
                else
                {
                }

                m_params.SetConfig(m_configNumber, config);

                if (updateScanSchedule)
                {
                    ScheduleScan(config);
                }
                if (updateDataGridView)
                {
                    SetDataGridViewState();
                }
                UpdateUI();
            }
        }

        private void rb_CheckedChanged(object sender, EventArgs e)
        {
            if (m_blockParamUpdate == false)
            {
                CyConfigModel config = m_params.GetConfig(m_configNumber);
                bool updateScanSchedule = false;

                if (sender == m_rbOneShot || sender == m_rbFreeRunning)
                {
                    config.FreeRunning = m_rbFreeRunning.Checked;
                    updateScanSchedule = true;
                }

                m_params.SetConfig(m_configNumber, config);

                if (updateScanSchedule)
                {
                    ScheduleScan(config);
                }
                config.OnSideEffectChange();
            }
        }

        protected override void OnValidating(CancelEventArgs e)
        {
            // Call Value property to reread text (in case NumericUpDown is still editing).
            // This will trigger ValueChanged/TextChanged if necessary.
            decimal unused = m_nudSampleRate.Value;
            unused = m_nudHighLimit.Value;
            unused = m_nudLowLimit.Value;
            unused = m_nudSequencedChannels.Value;
            unused = m_nudVrefVoltage.Value;
            base.OnValidating(e);
        }

        public static decimal? GetNumUpDownValue(NumericUpDown control)
        {
            decimal value;
            if (control.ContainsFocus)
            {
                // There is a possibility that the value may be invalid (empty string) or
                // out of range during editing. Such values will be ignored.
                // If the control is focused, the Value getter will reset the text and cursor.
                // To avoid interfering with editing, read the Text property instead.
                string text = control.Text;
                if (control.Hexadecimal)
                {
                    uint uintVal;
                    if (!uint.TryParse(text, NumberStyles.HexNumber, NumberFormatInfo.CurrentInfo, out uintVal))
                        return null;    // Ignore invalid value
                    value = uintVal;
                }
                else if (!decimal.TryParse(text, out value))
                    return null;    // Ignore invalid value

                if (value < control.Minimum || value > control.Maximum)
                    return Math.Min(control.Maximum, Math.Max(control.Minimum, value));    // Saturate out-of-range values.
            }
            else
                value = control.Value;
            return value;
        }

        private static void SetNumUpDownValue(NumericUpDown control, decimal newValue, decimal min, decimal max)
        {
            if (control.Minimum != min)
                control.Minimum = min;
            if (control.Maximum != max)
                control.Maximum = max;
            SetNumUpDownValue(control, newValue);
        }

        private static void SetNumUpDownValue(NumericUpDown control, decimal newValue)
        {
            decimal? oldValue = GetNumUpDownValue(control);
            if (!oldValue.HasValue || oldValue.Value != newValue)
            {
                newValue = Math.Max(control.Minimum, Math.Min(newValue, control.Maximum));
                control.Value = newValue;
            }
        }

        private void nud_TextChanged(object sender, EventArgs e)
        {
            // Normally the NumericUpDown doesn't send ValueChanged until it is unfocused.
            // To update dependent controls sooner, use TextChanged instead.
            NumericUpDown control = (NumericUpDown)sender;
            decimal? newValueNullable = GetNumUpDownValue(control);
            if (!newValueNullable.HasValue)
                return;
            decimal newValue = newValueNullable.Value;

            if (m_blockParamUpdate == false)
            {
                const double MIN_DIFFERENCE = 0.00001;
                CyConfigModel config = m_params.GetConfig(m_configNumber);
                bool changed = false;

                if (sender == m_nudHighLimit)
                {
                    if (Math.Abs(config.HighLimit - (double)newValue) > MIN_DIFFERENCE)
                        changed = true;
                    config.HighLimit = (double)newValue;
                }
                else if (sender == m_nudLowLimit)
                {
                    if (Math.Abs(config.LowLimit - (double)newValue) > MIN_DIFFERENCE)
                        changed = true;
                    config.LowLimit = (double)newValue;
                }
                else if (sender == m_nudSampleRate)
                {
                    if (Math.Abs(config.SampleRate - (double)newValue) > MIN_DIFFERENCE)
                        changed = true;
                    config.SampleRate = (double)newValue;
                }
                else if (sender == m_nudSequencedChannels)
                {
                    // m_nudSequencedChannels still uses ValueChanged to avoid excessive
                    // channel list modifications during editing. Don't use newValue here because
                    // it is based on the Text property which is out of date during ValueChanged.
                    config.NumChannels = (int)m_nudSequencedChannels.Value;
                    config.NumChannels = Math.Max(config.NumChannels, CyParamRanges.NUM_CHANNEL_MIN);
                    config.NumChannels = Math.Min(config.NumChannels, CyParamRanges.NUM_CHANNEL_MAX);
                    while (config.ChannelList.Count < config.NumChannels)
                    {
                        config.ChannelList.Add(new CyChannelModel());
                    }
                    while (config.ChannelList.Count > config.NumChannels)
                    {
                        config.ChannelList.RemoveAt(config.ChannelList.Count - 1);
                    }
                    if ((int)m_nudSequencedChannels.Value != config.NumChannels)
                    {
                        m_nudSequencedChannels.Value = config.NumChannels;
                    }
                    changed = true;
                }
                else if (sender == m_nudVrefVoltage)
                {
                    if (Math.Abs(config.VrefVoltage - (double)newValue) > MIN_DIFFERENCE)
                        changed = true;
                    config.VrefVoltage = (double)newValue;
                }

                if (changed)
                {
					m_params.SetConfig(m_configNumber, config);
                    ScheduleScan(config);
                    SetDataGridViewState();
                    UpdateUI();
                }
            }
        }


        private void cb_CheckedChanged(object sender, EventArgs e)
        {
            if (m_blockParamUpdate == false)
            {
                CyConfigModel config = m_params.GetConfig(m_configNumber);
                bool updateScanSchedule = false;

                if (sender == m_cbUseSoc)
                {
                    config.UseSoc = m_cbUseSoc.Checked;
                }
                else if (sender == m_cbVrefBypass)
                {
                    config.VrefBypass = m_cbVrefBypass.Checked;
                    updateScanSchedule = true;
                }

                m_params.SetConfig(m_configNumber, config);
                m_params.ExternalSoc = CyModelUtils.AnyConfigHasUseSoc(m_params);

                if (updateScanSchedule)
                {
                    ScheduleScan(config);
                }

                UpdateUI();
            }
        }

        private void dataGridView1_CellContentClick(object sender, System.Windows.Forms.DataGridViewCellEventArgs e)
        {
            if (m_blockParamUpdate == false)
            {
                dgv_ElementChanged(sender, e);
            }
        }

        private void dgv_ElementChanged(object sender, EventArgs e)
        {
            if (m_blockParamUpdate == false)
            {
                var config = m_params.GetConfig(m_configNumber);

                var channels = new List<CyChannelModel>();
                for (int row = 0; row < m_dgvChannels.Rows.Count; row++)
                {
                    var cbEnabled = (DataGridViewCheckBoxCell)m_dgvChannels[m_dgvcEnable.Index, row];
                    var enabled = (Boolean)cbEnabled.Value;

                    var altResolution = (bool) m_dgvChannels[m_dgvcResolution.Index, row].Value;

                    var inputMode = (CyEInputMode)m_dgvChannels[m_dgvcInputMode.Index, row].Value;

                    var cbAveraging = (DataGridViewCheckBoxCell)m_dgvChannels[m_dgvcAverage.Index, row];
                    var useAveraging = (Boolean)cbAveraging.Value;

                    double acqTime;
                    var tbAcqTime = (DataGridViewTextBoxCell)m_dgvChannels[m_dgvcAcqTime.Index, row];
                    Double.TryParse(tbAcqTime.Value.ToString(), out acqTime);
                    if (acqTime < CyParamRanges.APERTURE_MIN_NS)
                    {
                        acqTime = CyParamRanges.APERTURE_MIN_NS;
                    }
                    if (inputMode == CyEInputMode.FILTER_CHAN)
                    {
                        if (acqTime < CyParamRanges.APERTURE_FILTER_MIN_NS)
                        {
                            acqTime = CyParamRanges.APERTURE_FILTER_MIN_NS;
                        }
                    }

                    var cbLimitIntr = (DataGridViewCheckBoxCell)m_dgvChannels[m_dgvcLimitInterrupt.Index, row];
                    var limitInterrupt = (Boolean)cbLimitIntr.Value;

                    var cbSatIntr = (DataGridViewCheckBoxCell)m_dgvChannels[m_dgvcSaturationInterrupt.Index, row];
                    var saturationInterrupt = (Boolean)cbSatIntr.Value;

                    var channelModel = new CyChannelModel(enabled, altResolution, inputMode,
                        useAveraging, acqTime, limitInterrupt, saturationInterrupt);
                    channels.Add(channelModel);
                }

                config.ChannelList = channels;
                ScheduleScan(config);
                config.OnSideEffectChange();
            }
        }

        private void AdcClockSourceChanged()
        {
            ScheduleScanWithNewClockSource();
            var config = m_params.GetConfig(m_configNumber);
            config.OnSideEffectChange();
        }

        private void ScheduleScanWithNewClockSource()
        {
            if (CyModelUtils.InvalidAdcClock(m_params))
            {
                // Do not schedule scan.
            }
            else
            {
                var config = m_params.GetConfig(ConfigNumber);

                ScheduleScan(config);
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
            OnSchedulerErrorsChange(schedErrs);
            config.UpdateScanRateLimits(clkData, isClkExternal);
        }

        private void dgv_ElementDirty(object sender, EventArgs e)
        {
            if (m_dgvChannels.IsCurrentCellDirty)
            {
                m_dgvChannels.CommitEdit(DataGridViewDataErrorContexts.Commit);
            }
        }
        private double CalculateActualAcqTime_ns(int chanNum)
        {
            CyConfigModel config = m_params.GetConfig(m_configNumber);
            double acqTime = config.ChannelList[chanNum].ActualAcqTime;

            return acqTime;
        }
        private double CalculateMaxResist_ohm()
        {
            return 0.0;
        }

        private void m_dgvChannelConfigs_DataError(object sender, DataGridViewDataErrorEventArgs e)
        {
        }

        private void m_convToolTip_Popup(object sender, PopupEventArgs e)
        {
        }

        private void m_lDiffHighLimitVolts_Click(object sender, EventArgs e)
        {

        }

        private void tableLayoutPanel1_Paint(object sender, PaintEventArgs e)
        {

        }

        private void m_dgvChannels_CellClick(object sender, DataGridViewCellEventArgs e)
        {
            // Adapted from http://stackoverflow.com/questions/13005112
            // to change background color to white and drop down the menu on mouse click.
            // CDT 233575

            var datagridview = sender as DataGridView;
            bool validRow = (e.RowIndex != -1) && (!datagridview.Rows[e.RowIndex].ReadOnly); //Make sure the clicked row isn't the header.

            // Check to make sure the cell clicked is the cell containing the combobox 
            if (datagridview.Columns[e.ColumnIndex] is DataGridViewComboBoxColumn && validRow)
            {
                datagridview.BeginEdit(true);
                ((ComboBox)datagridview.EditingControl).BackColor = Color.White;
                ((ComboBox)datagridview.EditingControl).DroppedDown = true;
            }
        }

        private void m_dgvChannels_KeyPress(object sender, KeyPressEventArgs e)
        {
        }

        private void m_dgvChannels_KeyDown(object sender, KeyEventArgs e)
        {
            if (e.KeyCode == Keys.Enter)
            {
                return;
            }

        }
    }
}
