using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Drawing;
using System.Data;
using System.Text;
using System.Windows.Forms;

namespace ADC_UAB_v1_0
{
    partial class ADC_UAB_Control
    {
        /// <summary> 
        /// Required designer variable.
        /// </summary>
        private System.ComponentModel.IContainer components = null;

        // Begin parameter control declarations
        // End parameter control declarations

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
        
        // Updates form with saved parameters when the GUI is opened.
        public void UpdateForm()
        {
            // Begin parameter custom control update
            // End parameter custom control update

            // Begin parameter default control update
            int vrefOffset = (int) parameters.VrefSource * 5;
            m_cmbGain.SelectedIndex = (int)parameters.VRange + vrefOffset;


            switch (this.parameters.Endedness)
            {
                case CyEInputEndedness.Differential:
                    this.m_rbDifferential.Checked = true;
                    this.m_rbSingleEnded.Checked = false;
                    break;
                default:
                    this.m_rbDifferential.Checked = false;
                    this.m_rbSingleEnded.Checked = true;
                    break;
            }

            switch (this.parameters.ShowSoc)
            {
                case true:
                    this.m_rbHardware.Checked = true;
                    this.m_rbSoftware.Checked = false;
                    break;
                default:
                    this.m_rbHardware.Checked = false;
                    this.m_rbSoftware.Checked = true;
                    break;
            }
            // End parameter default control update

            SetToolTips();
        }

        #region Windows Form Designer generated code

        private void InitializeComponent()
        {
            this.components = new System.ComponentModel.Container();
            System.ComponentModel.ComponentResourceManager resources = new System.ComponentModel.ComponentResourceManager(typeof(ADC_UAB_Control));
            this.m_lbGain = new System.Windows.Forms.Label();
            this.m_gbTiming = new System.Windows.Forms.GroupBox();
            this.m_lMaxSourceImp = new System.Windows.Forms.Label();
            this.m_lConvTime = new System.Windows.Forms.Label();
            this.m_lbConvTime = new System.Windows.Forms.Label();
            this.m_lbMaxSourceImp = new System.Windows.Forms.Label();
            this.m_gbInput = new System.Windows.Forms.GroupBox();
            this.m_rbDifferential = new System.Windows.Forms.RadioButton();
            this.m_rbSingleEnded = new System.Windows.Forms.RadioButton();
            this.m_cmbGain = new System.Windows.Forms.ComboBox();
            this.m_gbReference = new System.Windows.Forms.GroupBox();
            this.m_toolTip = new System.Windows.Forms.ToolTip(this.components);
            this.tableLayoutPanel1 = new System.Windows.Forms.TableLayoutPanel();
            this.m_lVoltsMin = new System.Windows.Forms.Label();
            this.m_lVoltsMid = new System.Windows.Forms.Label();
            this.m_lCodeMid = new System.Windows.Forms.Label();
            this.m_lCodeMin = new System.Windows.Forms.Label();
            this.m_lVoltsMax = new System.Windows.Forms.Label();
            this.m_lCodeMax = new System.Windows.Forms.Label();
            this.m_lRowMin = new System.Windows.Forms.Label();
            this.m_lRowMax = new System.Windows.Forms.Label();
            this.m_lRowMid = new System.Windows.Forms.Label();
            this.m_lVoltsHeader = new System.Windows.Forms.Label();
            this.m_lCodeHeader = new System.Windows.Forms.Label();
            this.m_lRowHeader = new System.Windows.Forms.Label();
            this.m_gbTransfer = new System.Windows.Forms.GroupBox();
            this.m_gbTrigger = new System.Windows.Forms.GroupBox();
            this.m_rbHardware = new System.Windows.Forms.RadioButton();
            this.m_rbSoftware = new System.Windows.Forms.RadioButton();
            this.m_warningProvider = new System.Windows.Forms.ErrorProvider(this.components);
            this.m_noteProvider = new System.Windows.Forms.ErrorProvider(this.components);
            this.m_gbTiming.SuspendLayout();
            this.m_gbInput.SuspendLayout();
            this.m_gbReference.SuspendLayout();
            this.tableLayoutPanel1.SuspendLayout();
            this.m_gbTransfer.SuspendLayout();
            this.m_gbTrigger.SuspendLayout();
            ((System.ComponentModel.ISupportInitialize)(this.m_warningProvider)).BeginInit();
            ((System.ComponentModel.ISupportInitialize)(this.m_noteProvider)).BeginInit();
            this.SuspendLayout();
            // 
            // m_lbGain
            // 
            this.m_lbGain.AutoSize = true;
            this.m_lbGain.Location = new System.Drawing.Point(6, 22);
            this.m_lbGain.Name = "m_lbGain";
            this.m_lbGain.Size = new System.Drawing.Size(64, 13);
            this.m_lbGain.TabIndex = 4;
            this.m_lbGain.Text = "Input range:";
            this.m_toolTip.SetToolTip(this.m_lbGain, "blanktooltip");
            // 
            // m_gbTiming
            // 
            this.m_gbTiming.Controls.Add(this.m_lMaxSourceImp);
            this.m_gbTiming.Controls.Add(this.m_lConvTime);
            this.m_gbTiming.Controls.Add(this.m_lbConvTime);
            this.m_gbTiming.Controls.Add(this.m_lbMaxSourceImp);
            this.m_gbTiming.Location = new System.Drawing.Point(0, 134);
            this.m_gbTiming.Name = "m_gbTiming";
            this.m_gbTiming.Size = new System.Drawing.Size(309, 68);
            this.m_gbTiming.TabIndex = 13;
            this.m_gbTiming.TabStop = false;
            this.m_gbTiming.Text = "Timing";
            // 
            // m_lMaxSourceImp
            // 
            this.m_lMaxSourceImp.AutoSize = true;
            this.m_lMaxSourceImp.Location = new System.Drawing.Point(248, 43);
            this.m_lMaxSourceImp.Name = "m_lMaxSourceImp";
            this.m_lMaxSourceImp.Size = new System.Drawing.Size(22, 13);
            this.m_lMaxSourceImp.TabIndex = 33;
            this.m_lMaxSourceImp.Text = "5 k";
            // 
            // m_lConvTime
            // 
            this.m_lConvTime.AutoSize = true;
            this.m_lConvTime.Location = new System.Drawing.Point(248, 16);
            this.m_lConvTime.Name = "m_lConvTime";
            this.m_lConvTime.Size = new System.Drawing.Size(42, 13);
            this.m_lConvTime.TabIndex = 32;
            this.m_lConvTime.Text = "1.05 us";
            // 
            // m_lbConvTime
            // 
            this.m_lbConvTime.Anchor = ((System.Windows.Forms.AnchorStyles)(((System.Windows.Forms.AnchorStyles.Top | System.Windows.Forms.AnchorStyles.Left) 
            | System.Windows.Forms.AnchorStyles.Right)));
            this.m_lbConvTime.AutoSize = true;
            this.m_lbConvTime.Location = new System.Drawing.Point(6, 16);
            this.m_lbConvTime.Name = "m_lbConvTime";
            this.m_lbConvTime.Size = new System.Drawing.Size(85, 13);
            this.m_lbConvTime.TabIndex = 3;
            this.m_lbConvTime.Text = "Conversion time:";
            this.m_toolTip.SetToolTip(this.m_lbConvTime, "blanktooltip");
            // 
            // m_lbMaxSourceImp
            // 
            this.m_lbMaxSourceImp.AutoSize = true;
            this.m_lbMaxSourceImp.Location = new System.Drawing.Point(6, 43);
            this.m_lbMaxSourceImp.Name = "m_lbMaxSourceImp";
            this.m_lbMaxSourceImp.Size = new System.Drawing.Size(120, 13);
            this.m_lbMaxSourceImp.TabIndex = 5;
            this.m_lbMaxSourceImp.Text = "Max source impedance:";
            // 
            // m_gbInput
            // 
            this.m_gbInput.Controls.Add(this.m_rbDifferential);
            this.m_gbInput.Controls.Add(this.m_rbSingleEnded);
            this.m_gbInput.Location = new System.Drawing.Point(3, 3);
            this.m_gbInput.Name = "m_gbInput";
            this.m_gbInput.Size = new System.Drawing.Size(306, 68);
            this.m_gbInput.TabIndex = 14;
            this.m_gbInput.TabStop = false;
            this.m_gbInput.Text = "Input";
            // 
            // m_rbDifferential
            // 
            this.m_rbDifferential.AutoSize = true;
            this.m_rbDifferential.Location = new System.Drawing.Point(9, 19);
            this.m_rbDifferential.Name = "m_rbDifferential";
            this.m_rbDifferential.Size = new System.Drawing.Size(75, 17);
            this.m_rbDifferential.TabIndex = 1;
            this.m_rbDifferential.TabStop = true;
            this.m_rbDifferential.Text = "Differential";
            this.m_toolTip.SetToolTip(this.m_rbDifferential, "blanktooltip");
            this.m_rbDifferential.UseVisualStyleBackColor = true;
            this.m_rbDifferential.CheckedChanged += new System.EventHandler(this.m_rbDifferential_CheckedChanged);
            // 
            // m_rbSingleEnded
            // 
            this.m_rbSingleEnded.AutoSize = true;
            this.m_rbSingleEnded.Location = new System.Drawing.Point(9, 42);
            this.m_rbSingleEnded.Name = "m_rbSingleEnded";
            this.m_rbSingleEnded.Size = new System.Drawing.Size(87, 17);
            this.m_rbSingleEnded.TabIndex = 2;
            this.m_rbSingleEnded.TabStop = true;
            this.m_rbSingleEnded.Text = "Single-ended";
            this.m_toolTip.SetToolTip(this.m_rbSingleEnded, "blanktooltip");
            this.m_rbSingleEnded.UseVisualStyleBackColor = true;
            this.m_rbSingleEnded.CheckedChanged += new System.EventHandler(this.m_rbSingleEnded_CheckedChanged);
            // 
            // m_cmbGain
            // 
            this.m_cmbGain.DropDownStyle = System.Windows.Forms.ComboBoxStyle.DropDownList;
            this.m_cmbGain.FormattingEnabled = true;
            this.m_cmbGain.Items.AddRange(new object[] {
            "±2.4V",
            "±1.2V",
            "±0.6V",
            "±0.3V",
            "±0.15V",
            "±Vref",
            "±Vref/2",
            "±Vref/4",
            "±Vref/8",
            "±Vref/16"});
            this.m_cmbGain.Location = new System.Drawing.Point(92, 19);
            this.m_cmbGain.Name = "m_cmbGain";
            this.m_cmbGain.Size = new System.Drawing.Size(208, 21);
            this.m_cmbGain.TabIndex = 7;
            this.m_toolTip.SetToolTip(this.m_cmbGain, "blanktooltip");
            this.m_cmbGain.SelectedIndexChanged += new System.EventHandler(this.m_cmbGain_SelectedIndexChanged);
            // 
            // m_gbReference
            // 
            this.m_gbReference.Controls.Add(this.m_lbGain);
            this.m_gbReference.Controls.Add(this.m_cmbGain);
            this.m_gbReference.Location = new System.Drawing.Point(3, 77);
            this.m_gbReference.Name = "m_gbReference";
            this.m_gbReference.Size = new System.Drawing.Size(306, 51);
            this.m_gbReference.TabIndex = 16;
            this.m_gbReference.TabStop = false;
            this.m_gbReference.Text = "Reference";
            // 
            // tableLayoutPanel1
            // 
            this.tableLayoutPanel1.ColumnCount = 3;
            this.tableLayoutPanel1.ColumnStyles.Add(new System.Windows.Forms.ColumnStyle(System.Windows.Forms.SizeType.Absolute, 42F));
            this.tableLayoutPanel1.ColumnStyles.Add(new System.Windows.Forms.ColumnStyle(System.Windows.Forms.SizeType.Percent, 23.28767F));
            this.tableLayoutPanel1.ColumnStyles.Add(new System.Windows.Forms.ColumnStyle(System.Windows.Forms.SizeType.Percent, 27.41936F));
            this.tableLayoutPanel1.Controls.Add(this.m_lVoltsMin, 2, 3);
            this.tableLayoutPanel1.Controls.Add(this.m_lVoltsMid, 2, 2);
            this.tableLayoutPanel1.Controls.Add(this.m_lCodeMid, 1, 2);
            this.tableLayoutPanel1.Controls.Add(this.m_lCodeMin, 1, 3);
            this.tableLayoutPanel1.Controls.Add(this.m_lVoltsMax, 2, 1);
            this.tableLayoutPanel1.Controls.Add(this.m_lCodeMax, 1, 1);
            this.tableLayoutPanel1.Controls.Add(this.m_lRowMin, 0, 3);
            this.tableLayoutPanel1.Controls.Add(this.m_lRowMax, 0, 1);
            this.tableLayoutPanel1.Controls.Add(this.m_lRowMid, 0, 2);
            this.tableLayoutPanel1.Controls.Add(this.m_lVoltsHeader, 2, 0);
            this.tableLayoutPanel1.Controls.Add(this.m_lCodeHeader, 1, 0);
            this.tableLayoutPanel1.Controls.Add(this.m_lRowHeader, 0, 0);
            this.tableLayoutPanel1.Location = new System.Drawing.Point(18, 19);
            this.tableLayoutPanel1.Name = "tableLayoutPanel1";
            this.tableLayoutPanel1.RowCount = 5;
            this.tableLayoutPanel1.RowStyles.Add(new System.Windows.Forms.RowStyle(System.Windows.Forms.SizeType.Absolute, 25F));
            this.tableLayoutPanel1.RowStyles.Add(new System.Windows.Forms.RowStyle(System.Windows.Forms.SizeType.Absolute, 25F));
            this.tableLayoutPanel1.RowStyles.Add(new System.Windows.Forms.RowStyle(System.Windows.Forms.SizeType.Absolute, 25F));
            this.tableLayoutPanel1.RowStyles.Add(new System.Windows.Forms.RowStyle(System.Windows.Forms.SizeType.Absolute, 25F));
            this.tableLayoutPanel1.RowStyles.Add(new System.Windows.Forms.RowStyle(System.Windows.Forms.SizeType.Absolute, 20F));
            this.tableLayoutPanel1.Size = new System.Drawing.Size(162, 99);
            this.tableLayoutPanel1.TabIndex = 17;
            // 
            // m_lVoltsMin
            // 
            this.m_lVoltsMin.AutoSize = true;
            this.m_lVoltsMin.Location = new System.Drawing.Point(100, 75);
            this.m_lVoltsMin.Name = "m_lVoltsMin";
            this.m_lVoltsMin.Size = new System.Drawing.Size(23, 13);
            this.m_lVoltsMin.TabIndex = 28;
            this.m_lVoltsMin.Text = "0 V";
            // 
            // m_lVoltsMid
            // 
            this.m_lVoltsMid.AutoSize = true;
            this.m_lVoltsMid.Location = new System.Drawing.Point(100, 50);
            this.m_lVoltsMid.Name = "m_lVoltsMid";
            this.m_lVoltsMid.Size = new System.Drawing.Size(29, 13);
            this.m_lVoltsMid.TabIndex = 29;
            this.m_lVoltsMid.Text = "1.2V";
            // 
            // m_lCodeMid
            // 
            this.m_lCodeMid.AutoSize = true;
            this.m_lCodeMid.Location = new System.Drawing.Point(45, 50);
            this.m_lCodeMid.Name = "m_lCodeMid";
            this.m_lCodeMid.Size = new System.Drawing.Size(13, 13);
            this.m_lCodeMid.TabIndex = 24;
            this.m_lCodeMid.Text = "0";
            // 
            // m_lCodeMin
            // 
            this.m_lCodeMin.AutoSize = true;
            this.m_lCodeMin.Location = new System.Drawing.Point(45, 75);
            this.m_lCodeMin.Name = "m_lCodeMin";
            this.m_lCodeMin.Size = new System.Drawing.Size(34, 13);
            this.m_lCodeMin.TabIndex = 26;
            this.m_lCodeMin.Text = "-8192";
            // 
            // m_lVoltsMax
            // 
            this.m_lVoltsMax.AutoSize = true;
            this.m_lVoltsMax.Location = new System.Drawing.Point(100, 25);
            this.m_lVoltsMax.Name = "m_lVoltsMax";
            this.m_lVoltsMax.Size = new System.Drawing.Size(29, 13);
            this.m_lVoltsMax.TabIndex = 27;
            this.m_lVoltsMax.Text = "2.4V";
            // 
            // m_lCodeMax
            // 
            this.m_lCodeMax.AutoSize = true;
            this.m_lCodeMax.Location = new System.Drawing.Point(45, 25);
            this.m_lCodeMax.Name = "m_lCodeMax";
            this.m_lCodeMax.Size = new System.Drawing.Size(31, 13);
            this.m_lCodeMax.TabIndex = 23;
            this.m_lCodeMax.Text = "8191";
            // 
            // m_lRowMin
            // 
            this.m_lRowMin.AutoSize = true;
            this.m_lRowMin.Location = new System.Drawing.Point(3, 75);
            this.m_lRowMin.Name = "m_lRowMin";
            this.m_lRowMin.Size = new System.Drawing.Size(24, 13);
            this.m_lRowMin.TabIndex = 25;
            this.m_lRowMin.Text = "Min";
            // 
            // m_lRowMax
            // 
            this.m_lRowMax.AutoSize = true;
            this.m_lRowMax.Location = new System.Drawing.Point(3, 25);
            this.m_lRowMax.Name = "m_lRowMax";
            this.m_lRowMax.Size = new System.Drawing.Size(27, 13);
            this.m_lRowMax.TabIndex = 23;
            this.m_lRowMax.Text = "Max";
            // 
            // m_lRowMid
            // 
            this.m_lRowMid.AutoSize = true;
            this.m_lRowMid.Location = new System.Drawing.Point(3, 50);
            this.m_lRowMid.Name = "m_lRowMid";
            this.m_lRowMid.Size = new System.Drawing.Size(24, 13);
            this.m_lRowMid.TabIndex = 24;
            this.m_lRowMid.Text = "Mid";
            // 
            // m_lVoltsHeader
            // 
            this.m_lVoltsHeader.AutoSize = true;
            this.m_lVoltsHeader.Location = new System.Drawing.Point(100, 0);
            this.m_lVoltsHeader.Name = "m_lVoltsHeader";
            this.m_lVoltsHeader.Size = new System.Drawing.Size(30, 13);
            this.m_lVoltsHeader.TabIndex = 21;
            this.m_lVoltsHeader.Text = "Volts";
            // 
            // m_lCodeHeader
            // 
            this.m_lCodeHeader.AutoSize = true;
            this.m_lCodeHeader.Location = new System.Drawing.Point(45, 0);
            this.m_lCodeHeader.Name = "m_lCodeHeader";
            this.m_lCodeHeader.Size = new System.Drawing.Size(32, 13);
            this.m_lCodeHeader.TabIndex = 20;
            this.m_lCodeHeader.Text = "Code";
            // 
            // m_lRowHeader
            // 
            this.m_lRowHeader.AutoSize = true;
            this.m_lRowHeader.Location = new System.Drawing.Point(3, 0);
            this.m_lRowHeader.Name = "m_lRowHeader";
            this.m_lRowHeader.Size = new System.Drawing.Size(0, 13);
            this.m_lRowHeader.TabIndex = 20;
            // 
            // m_gbTransfer
            // 
            this.m_gbTransfer.Controls.Add(this.tableLayoutPanel1);
            this.m_gbTransfer.Location = new System.Drawing.Point(315, 3);
            this.m_gbTransfer.Name = "m_gbTransfer";
            this.m_gbTransfer.Size = new System.Drawing.Size(191, 131);
            this.m_gbTransfer.TabIndex = 18;
            this.m_gbTransfer.TabStop = false;
            this.m_gbTransfer.Text = "Transfer Function";
            // 
            // m_gbTrigger
            // 
            this.m_gbTrigger.Controls.Add(this.m_rbHardware);
            this.m_gbTrigger.Controls.Add(this.m_rbSoftware);
            this.m_gbTrigger.Location = new System.Drawing.Point(315, 140);
            this.m_gbTrigger.Name = "m_gbTrigger";
            this.m_gbTrigger.Size = new System.Drawing.Size(110, 67);
            this.m_gbTrigger.TabIndex = 19;
            this.m_gbTrigger.TabStop = false;
            this.m_gbTrigger.Text = "Trigger";
            this.m_gbTrigger.Visible = false;
            // 
            // m_rbHardware
            // 
            this.m_rbHardware.AutoSize = true;
            this.m_rbHardware.Enabled = false;
            this.m_rbHardware.Location = new System.Drawing.Point(7, 18);
            this.m_rbHardware.Name = "m_rbHardware";
            this.m_rbHardware.Size = new System.Drawing.Size(71, 17);
            this.m_rbHardware.TabIndex = 3;
            this.m_rbHardware.TabStop = true;
            this.m_rbHardware.Text = "Hardware";
            this.m_rbHardware.UseVisualStyleBackColor = true;
            this.m_rbHardware.Visible = false;
            this.m_rbHardware.CheckedChanged += new System.EventHandler(this.m_rbHardware_CheckedChanged);
            // 
            // m_rbSoftware
            // 
            this.m_rbSoftware.AutoSize = true;
            this.m_rbSoftware.Enabled = false;
            this.m_rbSoftware.Location = new System.Drawing.Point(7, 41);
            this.m_rbSoftware.Name = "m_rbSoftware";
            this.m_rbSoftware.Size = new System.Drawing.Size(67, 17);
            this.m_rbSoftware.TabIndex = 3;
            this.m_rbSoftware.TabStop = true;
            this.m_rbSoftware.Text = "Software";
            this.m_rbSoftware.UseVisualStyleBackColor = true;
            this.m_rbSoftware.Visible = false;
            this.m_rbSoftware.CheckedChanged += new System.EventHandler(this.m_rbSoftware_CheckedChanged);
            // 
            // m_warningProvider
            // 
            this.m_warningProvider.ContainerControl = this;
            // 
            // m_noteProvider
            // 
            this.m_noteProvider.BlinkStyle = System.Windows.Forms.ErrorBlinkStyle.NeverBlink;
            this.m_noteProvider.ContainerControl = this;
            this.m_noteProvider.Icon = ((System.Drawing.Icon)(resources.GetObject("m_noteProvider.Icon")));
            // 
            // ADC_UAB_Control
            // 
            this.Controls.Add(this.m_gbInput);
            this.Controls.Add(this.m_gbTrigger);
            this.Controls.Add(this.m_gbReference);
            this.Controls.Add(this.m_gbTiming);
            this.Controls.Add(this.m_gbTransfer);
            this.Name = "ADC_UAB_Control";
            this.Size = new System.Drawing.Size(512, 210);
            this.m_gbTiming.ResumeLayout(false);
            this.m_gbTiming.PerformLayout();
            this.m_gbInput.ResumeLayout(false);
            this.m_gbInput.PerformLayout();
            this.m_gbReference.ResumeLayout(false);
            this.m_gbReference.PerformLayout();
            this.tableLayoutPanel1.ResumeLayout(false);
            this.tableLayoutPanel1.PerformLayout();
            this.m_gbTransfer.ResumeLayout(false);
            this.m_gbTrigger.ResumeLayout(false);
            this.m_gbTrigger.PerformLayout();
            ((System.ComponentModel.ISupportInitialize)(this.m_warningProvider)).EndInit();
            ((System.ComponentModel.ISupportInitialize)(this.m_noteProvider)).EndInit();
            this.ResumeLayout(false);

        }

        #endregion

        private Label m_lbGain;
        private GroupBox m_gbTiming;
        private Label m_lbConvTime;
        private GroupBox m_gbInput;
        private RadioButton m_rbSingleEnded;
        private RadioButton m_rbDifferential;
        private ComboBox m_cmbGain;
        private GroupBox m_gbReference;
        private ToolTip m_toolTip;
        private Label m_lbMaxSourceImp;
        private TableLayoutPanel tableLayoutPanel1;
        private GroupBox m_gbTransfer;
        private GroupBox m_gbTrigger;
        private RadioButton m_rbHardware;
        private RadioButton m_rbSoftware;
        private ErrorProvider m_warningProvider;
        private ErrorProvider m_noteProvider;
        private Label m_lRowHeader;
        private Label m_lCodeHeader;
        private Label m_lVoltsHeader;
        private Label m_lRowMax;
        private Label m_lRowMin;
        private Label m_lRowMid;
        private Label m_lCodeMax;
        private Label m_lCodeMin;
        private Label m_lVoltsMid;
        private Label m_lCodeMid;
        private Label m_lVoltsMax;
        private Label m_lVoltsMin;
        private Label m_lConvTime;
        private Label m_lMaxSourceImp;
    }
}
