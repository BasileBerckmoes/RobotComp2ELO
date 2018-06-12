/*******************************************************************************
* Copyright 2008-2012, Cypress Semiconductor Corporation.  All rights reserved.
* You may use this file only in accordance with the license, terms, conditions, 
* disclaimers, and limitations in the end user license agreement accompanying 
* the software package with which this file was provided.
********************************************************************************/

using System;
using System.Collections.Generic;
using System.Text;
using System.Windows.Forms;
using CyDesigner.Extensions.Gde;
using CyDesigner.Extensions.Common;
using System.Drawing;
using BoostConv_v5_0.Properties;

namespace BoostConv_v5_0
{
    enum EditorMode
    {
        Loading,
        CustomEditing,
        ExpressionEditing
    }

    public class CyConfigurationTab : UserControl, ICyParamEditingControl
    {
        #region Private members
        const string STR_MAX_OUTPUT_CURRENT = "Max output current (mA): ";
        private CyParameters m_parameters;
        private ErrorProvider errorProvider;
        private System.ComponentModel.IContainer components;
        private CheckBox cbDisablesAutoBattery;
        #endregion

        #region Properties
        public double InputVoltage
        {
            get { return GetComboBoxValue(cbInputVol); }
            set { cbInputVol.SelectedItem = value.ToString(); }
        }

        public byte OutVoltage
        {
            get { return (cbOutputVol.SelectedIndex == 0) ? (byte)0 : (byte)(cbOutputVol.SelectedIndex + 2); }
            set
            {
                int index = (value == 0) ? 0 : (int)(value - 2);
                SetComboBoxIndex(cbOutputVol, index);
            }
        }
        #endregion

        #region Ctors
        public CyConfigurationTab(CyParameters parameters)
        {
            InitializeComponent();

            m_parameters = parameters;

            Dock = DockStyle.Fill;
            cbOutputVol.Items.Clear();
            cbOutputVol.Items.AddRange(CyParameters.m_outputValuesRange);
            cbOutputVol.Items[0] = "Off";
            CyParameters.FillEnum(cbSwFreq, typeof(CyFrequency));

            CyParameters.FillEnum(cbExternalClock, typeof(CyClockFr));

            UpdateParam();

            //This field will be enabled when characterization data will be obtained
            label_outCurrent.Visible = false;
            updown_outCurrent.Visible = false;

        }
        #endregion

        #region Public methods
        public void UpdateParam()
        {
            InitializeInputVoltageComboBox();
            InputVoltage = m_parameters.InputVoltage;

            OutVoltage = m_parameters.OutVoltage;

            CyParameters.SetValue(cbSwFreq, m_parameters.Frequency);
            // Disable changing from 400KHz to 32KHz
            if (m_parameters.Frequency == CyFrequency.SWITCH_FREQ_400KHZ)
            {
                cbSwFreq.Enabled = false;
                cbSwFreq.Visible = false;
                labelSwFreq.Text = cbSwFreq.Text;
                labelSwFreq.Enabled = true;
                labelSwFreq.Visible = true;
            }
            else
            {
                labelSwFreq.Enabled = false;
                labelSwFreq.Visible = false;
                cbSwFreq.Enabled = true;
                cbSwFreq.Visible = true;                
            }

            CyParameters.SetValue(cbExternalClock, m_parameters.ExternalClockSrc);
            // Disable changing External Clock to other value then 'Normal' for PSoC5LP device
            if (m_parameters.ExternalClockSrc == CyClockFr.EXTCLK_NONE && m_parameters.IsPSoC5LP())
            {
                cbExternalClock.Enabled = false;
                cbExternalClock.Visible = false;
                labelExternalClock.Text = cbExternalClock.Text;
                labelExternalClock.Enabled = true;
                labelExternalClock.Visible = true;
            }
            else
            {
                labelExternalClock.Enabled = false;
                labelExternalClock.Visible = false;
                cbExternalClock.Enabled = true;
                cbExternalClock.Visible = true;
            }

            cbDisablesAutoBattery.Checked = m_parameters.DisableAutoBattery;

            CheckMaxCurrent();
            SelectSchema();
            CheckClockSource();
        }
        #endregion

        #region Private tool methods
        private void InitializeInputVoltageComboBox()
        {
            List<object> comboBoxItems = new List<object>(new object[] {
                "0.5", "0.6", "0.7", "0.75", "0.8", "0.9", "1", "1.1", "1.2", "1.3", "1.4", "1.5", "1.6", "1.7", "1.8", 
                "1.9", "2", "2.1", "2.2", "2.3", "2.4", "2.5", "2.6", "2.7", "2.8", "2.9", "3", "3.1", "3.2", "3.3", 
                "3.4", "3.5", "3.6" 
            });

            if (comboBoxItems.Contains(m_parameters.InputVoltage.ToString()) == false)
            {
                double value;
                if (double.TryParse(m_parameters.InputVoltage.ToString(), out value))
                {
                    for (int i = 0; i < comboBoxItems.Count; i++)
                    {
                        if (Convert.ToDouble(comboBoxItems[i]) > value)
                        {
                            comboBoxItems.Insert(i, m_parameters.InputVoltage.ToString());
                            break;
                        }
                    }
                    if (comboBoxItems.Contains(m_parameters.InputVoltage.ToString()) == false)
                        comboBoxItems.Add(m_parameters.InputVoltage.ToString());
                }
            }

            this.cbInputVol.Items.Clear();
            this.cbInputVol.Items.AddRange(comboBoxItems.ToArray());
            this.cbInputVol.Text = m_parameters.InputVoltage.ToString();
        }

        private double GetComboBoxValue(ComboBox combo)
        {
            double result = 0;
            bool is_parsible = false;
            if (combo.SelectedItem != null)
                is_parsible = double.TryParse(combo.SelectedItem.ToString(), out result);
            System.Diagnostics.Debug.Assert(is_parsible);
            return result;
        }
        private void SetComboBoxIndex(ComboBox combo, int index)
        {
            if (combo.Items.Count > index && index > -2)
                combo.SelectedIndex = index;
            else
                System.Diagnostics.Debug.Assert(false);
        }
        private double GetVOutValue()
        {
            //First value is not double
            if (cbOutputVol.SelectedIndex == 0)
                return 0;

            double res = GetComboBoxValue(cbOutputVol);
            return res;
        }

        private void CheckMaxCurrent()
        {
            double vBatIn = InputVoltage;
            double vOut = GetVOutValue();
            int maxCurrent = 50;

            if (m_parameters.IsPSoC5LP())
            {
                if ((vBatIn >= 0.5) && (vBatIn < 1.6))
                {
                    maxCurrent = 15;
                }
                else if ((vBatIn >= 1.6) && (vBatIn <= 3.6) && (vOut > 3.6))
                {
                    maxCurrent = 50;
                }
                else if ((vBatIn >= 1.6) && (vBatIn <= 3.6) && (vOut <= 3.6))
                {
                    maxCurrent = 75;
                }
            }
            else //PSoC 3
            {
                if ((vBatIn >= 0.5) && (vBatIn < 0.8) && (vOut <= 3.6))
                {
                    maxCurrent = 15;
                }
                else if ((vBatIn >= 0.8) && (vBatIn < 1.6) && (vOut > 3.6))
                {
                    maxCurrent = 20;
                }
                else if ((vBatIn >= 0.8) && (vBatIn < 1.6) && (vOut <= 3.6))
                {
                    maxCurrent = 30;
                }
                else if ((vBatIn >= 1.6) && (vBatIn <= 3.6) && (vOut > 3.6))
                {
                    maxCurrent = 50;
                }
                else if ((vBatIn >= 1.6) && (vBatIn <= 3.6) && (vOut <= 3.6))
                {
                    maxCurrent = 75;
                }
            }

            updown_outCurrent.Maximum = maxCurrent;

            label_Current.Visible = label_Current_Value.Visible = (vOut <= 4.0 * vBatIn) && (vOut != 0);
            label_Current_Value.Text = maxCurrent.ToString();
        }
        public void CheckClockSource()
        {
            string error = string.Empty;
            if (m_parameters.ExternalClockSrc != CyClockFr.EXTCLK_NONE && m_parameters.IsPSoC5LP())
            {
                error = Properties.Resources.DRCClockSourcePSoC5LPLimit;
                this.errorProvider.Icon = m_iconError;
            }
            errorProvider.SetError(cbExternalClock, error);
        }

        private void SelectSchema()
        {
            if (m_parameters.IsPSoC5LP())
            {
                pictureB_schema.Image = (InputVoltage <= 0.9) || (GetVOutValue() >= 3.6) ? 
                    Resources.boost : Resources.boost_diodeless;
            }
            else
                pictureB_schema.Image = (GetVOutValue() > 3.6) ? Resources.boost : Resources.boost_diodeless;
        }
        Icon m_iconError = Icon.FromHandle(Properties.Resources.Symbol_Error.GetHicon());
        Icon m_iconWarning = Icon.FromHandle(Properties.Resources.WarningHS.GetHicon());
        private void CheckVoltageLimitation()
        {
            double vBatIn = InputVoltage;
            double vOut = GetVOutValue();

            // Check whether input voltage in range of minimum and maximum values
            // It may be out of range after either update from previous version or expression view modifications.
            if (vBatIn < CyParameters.MIN_INPUT_VOLTAGE || vBatIn > CyParameters.MAX_INPUT_VOLTAGE)
            {
                errorProvider.SetError(cbInputVol, string.Format(Properties.Resources.InputVoltageOutOfRange,
                    (CyParameters.MIN_INPUT_VOLTAGE), CyParameters.MAX_INPUT_VOLTAGE));
                this.errorProvider.Icon = m_iconError;
            }

            // At boost frequency of 2 MHz, VBOOST is limited to 2 x VBAT. At 400 kHz, VBOOST is limited to 4 x VBAT
            else if ((m_parameters.Frequency == CyFrequency.SWITCH_FREQ_400KHZ) && (vOut > 4.0 * vBatIn))
            {
                errorProvider.SetError(cbInputVol, Properties.Resources.VoltageErrorMessage400kHz);
                errorProvider.SetError(cbOutputVol, Properties.Resources.VoltageErrorMessage400kHz);
                errorProvider.SetError(cbSwFreq, Properties.Resources.VoltageErrorMessage400kHz);
                this.errorProvider.Icon = m_iconError;
            }
            else if ((vBatIn >= 0.5 && vBatIn < 0.8) && vOut > 3.6)
            {
                errorProvider.SetError(cbInputVol, Properties.Resources.InputVoltageErrorMessage);
                errorProvider.SetError(cbOutputVol, Properties.Resources.InputVoltageErrorMessage);
                this.errorProvider.Icon = m_iconError;
            }
            else if (vBatIn > vOut && vOut != 0)
            {
                errorProvider.SetError(cbInputVol, Properties.Resources.VoltageWarningMessage);
                errorProvider.SetError(cbOutputVol, Properties.Resources.VoltageWarningMessage);
                this.errorProvider.Icon = m_iconWarning;
            }
            else if ((m_parameters.Frequency == CyFrequency.SWITCH_FREQ_32KHZ) && m_parameters.IsPSoC5LP())
            {
                errorProvider.SetError(cbSwFreq, Properties.Resources.DRCSwitchingFreqPSoC5LPLimit);
                this.errorProvider.Icon = m_iconError;
            }
            else if ((m_parameters.Frequency == CyFrequency.SWITCH_FREQ_32KHZ) && m_parameters.IsPSoC3())
            {
                errorProvider.SetError(cbSwFreq, Properties.Resources.DRCSwitchingFreqPSoC3Limit);
                this.errorProvider.Icon = m_iconError;
            }
            else
            {
                errorProvider.SetError(cbInputVol, string.Empty);
                errorProvider.SetError(cbOutputVol, string.Empty);
                errorProvider.SetError(cbSwFreq, string.Empty);
            }
        }
        #endregion

        #region Event Handlers
        private void updown_outCurrent_ValueChanged(object sender, EventArgs e)
        {
            if (m_parameters.m_globalEditMode == false) return;

            m_parameters.OutCurrent = byte.Parse(updown_outCurrent.Value.ToString());
        }

        private void cbOutVoltage_SelectedIndexChanged(object sender, EventArgs e)
        {
            if (m_parameters.m_globalEditMode == false) return;

            CheckMaxCurrent();
            SelectSchema();

            m_parameters.OutVoltage = OutVoltage;
            CheckVoltageLimitation();
        }

        double m_prevInputVoltage = -1;
        private void cbInputVoltage_SelectedIndexChanged(object sender, EventArgs e)
        {
            if (InputVoltage < CyParameters.MIN_INPUT_VOLTAGE ||
                InputVoltage > CyParameters.MAX_INPUT_VOLTAGE)
            {
                m_prevInputVoltage = InputVoltage;
            }
            else
            {
                if (m_prevInputVoltage > 0)
                {
                    if (cbInputVol.Items.Contains(m_prevInputVoltage.ToString()))
                    {
                        cbInputVol.Items.Remove(m_prevInputVoltage.ToString());
                    }
                }
            }

            if (m_parameters.m_globalEditMode == false) return;

            CheckMaxCurrent();
            m_parameters.InputVoltage = InputVoltage;
            CheckVoltageLimitation();
            SelectSchema();
        }

        private void cbSwFreq_SelectedIndexChanged(object sender, EventArgs e)
        {
            m_parameters.Frequency = CyParameters.GetEnum<CyFrequency>(cbSwFreq.Text);
            
            CheckVoltageLimitation();
        }

        private void cbExternalClock_SelectedIndexChanged(object sender, EventArgs e)
        {
            m_parameters.ExternalClockSrc = CyParameters.GetEnum<CyClockFr>(cbExternalClock.Text);
            CheckClockSource();
        }

        private void cbDisablesAutoBattery_CheckedChanged(object sender, EventArgs e)
        {
            if (m_parameters.m_globalEditMode == false) return;

            m_parameters.DisableAutoBattery = cbDisablesAutoBattery.Checked;
        }
        #endregion

        #region ICyParamEditingControl Members

        public Control DisplayControl
        {
            get { return this; }
        }

        /// <summary>
        /// Gets any errors that exist for parameters on the DisplayControl.
        /// </summary>
        /// <returns></returns>
        public IEnumerable<CyCustErr> GetErrors()
        {
            List<CyCustErr> errs = new List<CyCustErr>();

            ICyInstQuery_v1 edit = m_parameters.m_edit;

            if (edit != null)
                foreach (string paramName in edit.GetParamNames())
                {
                    CyCompDevParam param = edit.GetCommittedParam(paramName);
                    if (param.IsVisible && param.TabName == CyParameters.P_CONFIG_PARAMETERS_TAB_NAME)
                    {
                        if (param.ErrorCount > 0)
                        {
                            foreach (string errMsg in param.Errors)
                            {
                                errs.Add(new CyCustErr(errMsg));
                            }
                        }
                    }
                }

            return errs;
        }


        #endregion

        #region Component Designer generated code
        private Label label_vOut;
        private ComboBox cbOutputVol;
        private Label label_outCurrent;
        private Label label_vBatIn;
        private NumericUpDown updown_outCurrent;
        private ComboBox cbInputVol;
        private Label label_Freq;
        private ComboBox cbSwFreq;
        private Label labelSwFreq;
        private Label label_Current;
        private Label label_Current_Value;
        private PictureBox pictureB_schema;
        private Label label_exClockSrc;
        private ComboBox cbExternalClock;
        private Label labelExternalClock;

        private void InitializeComponent()
        {
            this.components = new System.ComponentModel.Container();
            System.ComponentModel.ComponentResourceManager resources = new System.ComponentModel.ComponentResourceManager(typeof(CyConfigurationTab));
            this.label_vBatIn = new System.Windows.Forms.Label();
            this.label_vOut = new System.Windows.Forms.Label();
            this.cbOutputVol = new System.Windows.Forms.ComboBox();
            this.label_outCurrent = new System.Windows.Forms.Label();
            this.updown_outCurrent = new System.Windows.Forms.NumericUpDown();
            this.cbInputVol = new System.Windows.Forms.ComboBox();
            this.pictureB_schema = new System.Windows.Forms.PictureBox();
            this.label_Freq = new System.Windows.Forms.Label();
            this.cbSwFreq = new System.Windows.Forms.ComboBox();
            this.label_Current = new System.Windows.Forms.Label();
            this.label_exClockSrc = new System.Windows.Forms.Label();
            this.cbExternalClock = new System.Windows.Forms.ComboBox();
            this.errorProvider = new System.Windows.Forms.ErrorProvider(this.components);
            this.cbDisablesAutoBattery = new System.Windows.Forms.CheckBox();
            this.labelSwFreq = new System.Windows.Forms.Label();
            this.labelExternalClock = new System.Windows.Forms.Label();
            this.label_Current_Value = new System.Windows.Forms.Label();
            ((System.ComponentModel.ISupportInitialize)(this.updown_outCurrent)).BeginInit();
            ((System.ComponentModel.ISupportInitialize)(this.pictureB_schema)).BeginInit();
            ((System.ComponentModel.ISupportInitialize)(this.errorProvider)).BeginInit();
            this.SuspendLayout();
            // 
            // label_vBatIn
            // 
            this.label_vBatIn.AutoSize = true;
            this.label_vBatIn.Location = new System.Drawing.Point(3, 6);
            this.label_vBatIn.Name = "label_vBatIn";
            this.label_vBatIn.Size = new System.Drawing.Size(112, 13);
            this.label_vBatIn.TabIndex = 0;
            this.label_vBatIn.Text = "Vbat input voltage (V):";
            // 
            // label_vOut
            // 
            this.label_vOut.AutoSize = true;
            this.label_vOut.Location = new System.Drawing.Point(3, 33);
            this.label_vOut.Name = "label_vOut";
            this.label_vOut.Size = new System.Drawing.Size(96, 13);
            this.label_vOut.TabIndex = 2;
            this.label_vOut.Text = "Output voltage (V):";
            // 
            // cbOutputVol
            // 
            this.cbOutputVol.DropDownStyle = System.Windows.Forms.ComboBoxStyle.DropDownList;
            this.cbOutputVol.FormattingEnabled = true;
            this.cbOutputVol.Items.AddRange(new object[] {
            "Off",
            "1.8",
            "1.9",
            "2",
            "2.1",
            "2.2",
            "2.3",
            "2.4",
            "2.5",
            "2.6",
            "2.7",
            "2.8",
            "2.9",
            "3",
            "3.1",
            "3.2",
            "3.3",
            "3.4",
            "3.5",
            "3.6",
            "4",
            "4.25",
            "4.5",
            "4.75",
            "5",
            "5.25"});
            this.cbOutputVol.Location = new System.Drawing.Point(163, 30);
            this.cbOutputVol.Name = "cbOutputVol";
            this.cbOutputVol.Size = new System.Drawing.Size(94, 21);
            this.cbOutputVol.TabIndex = 3;
            this.cbOutputVol.SelectedIndexChanged += new System.EventHandler(this.cbOutVoltage_SelectedIndexChanged);
            // 
            // label_outCurrent
            // 
            this.label_outCurrent.Location = new System.Drawing.Point(3, 185);
            this.label_outCurrent.Name = "label_outCurrent";
            this.label_outCurrent.Size = new System.Drawing.Size(154, 41);
            this.label_outCurrent.TabIndex = 6;
            this.label_outCurrent.Text = "Estimated output current (mA):";
            // 
            // updown_outCurrent
            // 
            this.updown_outCurrent.Location = new System.Drawing.Point(163, 183);
            this.updown_outCurrent.Maximum = new decimal(new int[] {
            50,
            0,
            0,
            0});
            this.updown_outCurrent.Name = "updown_outCurrent";
            this.updown_outCurrent.Size = new System.Drawing.Size(94, 20);
            this.updown_outCurrent.TabIndex = 7;
            this.updown_outCurrent.ValueChanged += new System.EventHandler(this.updown_outCurrent_ValueChanged);
            // 
            // cbInputVol
            // 
            this.cbInputVol.DropDownStyle = System.Windows.Forms.ComboBoxStyle.DropDownList;
            this.cbInputVol.FormattingEnabled = true;
            this.cbInputVol.Items.AddRange(new object[] {
            "0.5",
            "0.6",
            "0.7",
            "0.8",
            "0.9",
            "1",
            "1.1",
            "1.2",
            "1.3",
            "1.4",
            "1.5",
            "1.6",
            "1.7",
            "1.8",
            "1.9",
            "2",
            "2.1",
            "2.2",
            "2.3",
            "2.4",
            "2.5",
            "2.6",
            "2.7",
            "2.8",
            "2.9",
            "3",
            "3.1",
            "3.2",
            "3.3",
            "3.4",
            "3.5",
            "3.6",
            "3.7",
            "3.8",
            "3.9",
            "4",
            "4.1",
            "4.2",
            "4.3",
            "4.4",
            "4.5",
            "4.6",
            "4.7",
            "4.8",
            "4.9",
            "5",
            "5.1",
            "5.2",
            "5.3",
            "5.4",
            "5.5"});
            this.cbInputVol.Location = new System.Drawing.Point(163, 3);
            this.cbInputVol.Name = "cbInputVol";
            this.cbInputVol.Size = new System.Drawing.Size(94, 21);
            this.cbInputVol.TabIndex = 1;
            this.cbInputVol.SelectedIndexChanged += new System.EventHandler(this.cbInputVoltage_SelectedIndexChanged);
            // 
            // pictureB_schema
            // 
            this.pictureB_schema.Anchor = ((System.Windows.Forms.AnchorStyles)((((System.Windows.Forms.AnchorStyles.Top | System.Windows.Forms.AnchorStyles.Bottom) 
            | System.Windows.Forms.AnchorStyles.Left) 
            | System.Windows.Forms.AnchorStyles.Right)));
            this.pictureB_schema.BorderStyle = System.Windows.Forms.BorderStyle.FixedSingle;
            this.pictureB_schema.Location = new System.Drawing.Point(278, 15);
            this.pictureB_schema.Name = "pictureB_schema";
            this.pictureB_schema.Size = new System.Drawing.Size(296, 245);
            this.pictureB_schema.SizeMode = System.Windows.Forms.PictureBoxSizeMode.StretchImage;
            this.pictureB_schema.TabIndex = 13;
            this.pictureB_schema.TabStop = false;
            // 
            // label_Freq
            // 
            this.label_Freq.AutoSize = true;
            this.label_Freq.Location = new System.Drawing.Point(3, 60);
            this.label_Freq.Name = "label_Freq";
            this.label_Freq.Size = new System.Drawing.Size(106, 13);
            this.label_Freq.TabIndex = 4;
            this.label_Freq.Text = "Switching frequency:";
            // 
            // cbSwFreq
            // 
            this.cbSwFreq.DropDownStyle = System.Windows.Forms.ComboBoxStyle.DropDownList;
            this.cbSwFreq.FormattingEnabled = true;
            this.cbSwFreq.Items.AddRange(new object[] {
            "400 kHz",
            "External 32 kHz"});
            this.cbSwFreq.Location = new System.Drawing.Point(163, 57);
            this.cbSwFreq.Name = "cbSwFreq";
            this.cbSwFreq.Size = new System.Drawing.Size(94, 21);
            this.cbSwFreq.TabIndex = 5;
            this.cbSwFreq.SelectedIndexChanged += new System.EventHandler(this.cbSwFreq_SelectedIndexChanged);
            // 
            // label_Current
            // 
            this.label_Current.AutoSize = true;
            this.label_Current.Location = new System.Drawing.Point(3, 117);
            this.label_Current.Name = "label_Current";
            this.label_Current.Size = new System.Drawing.Size(132, 13);
            this.label_Current.TabIndex = 6;
            this.label_Current.Text = "Max output current (mA):   ";
            // 
            // label_exClockSrc
            // 
            this.label_exClockSrc.AutoSize = true;
            this.label_exClockSrc.Location = new System.Drawing.Point(3, 87);
            this.label_exClockSrc.Name = "label_exClockSrc";
            this.label_exClockSrc.Size = new System.Drawing.Size(112, 13);
            this.label_exClockSrc.TabIndex = 2224;
            this.label_exClockSrc.Text = "External clock source:";
            // 
            // cbExternalClock
            // 
            this.cbExternalClock.DropDownStyle = System.Windows.Forms.ComboBoxStyle.DropDownList;
            this.cbExternalClock.FormattingEnabled = true;
            this.cbExternalClock.Items.AddRange(new object[] {
            "None",
            "ECO 32kHz",
            "ILO 32kHz"});
            this.cbExternalClock.Location = new System.Drawing.Point(163, 84);
            this.cbExternalClock.Name = "cbExternalClock";
            this.cbExternalClock.Size = new System.Drawing.Size(94, 21);
            this.cbExternalClock.TabIndex = 7;
            this.cbExternalClock.SelectedIndexChanged += new System.EventHandler(this.cbExternalClock_SelectedIndexChanged);
            // 
            // errorProvider
            // 
            this.errorProvider.BlinkStyle = System.Windows.Forms.ErrorBlinkStyle.NeverBlink;
            this.errorProvider.ContainerControl = this;
            this.errorProvider.Icon = ((System.Drawing.Icon)(resources.GetObject("errorProvider.Icon")));
            // 
            // cbDisablesAutoBattery
            // 
            this.cbDisablesAutoBattery.Location = new System.Drawing.Point(6, 133);
            this.cbDisablesAutoBattery.Name = "cbDisablesAutoBattery";
            this.cbDisablesAutoBattery.Size = new System.Drawing.Size(243, 49);
            this.cbDisablesAutoBattery.TabIndex = 30;
            this.cbDisablesAutoBattery.Text = "Disable auto battery connect to output when Vin = Vsel";
            this.cbDisablesAutoBattery.UseVisualStyleBackColor = true;
            this.cbDisablesAutoBattery.CheckedChanged += new System.EventHandler(this.cbDisablesAutoBattery_CheckedChanged);
            // 
            // labelSwFreq
            // 
            this.labelSwFreq.AutoSize = true;
            this.labelSwFreq.Location = new System.Drawing.Point(163, 61);
            this.labelSwFreq.Name = "labelSwFreq";
            this.labelSwFreq.Size = new System.Drawing.Size(57, 13);
            this.labelSwFreq.TabIndex = 2225;
            this.labelSwFreq.Text = "labSwFreq";
            // 
            // labelExternalClock
            // 
            this.labelExternalClock.AutoSize = true;
            this.labelExternalClock.Location = new System.Drawing.Point(163, 88);
            this.labelExternalClock.Name = "labelExternalClock";
            this.labelExternalClock.Size = new System.Drawing.Size(51, 13);
            this.labelExternalClock.TabIndex = 2226;
            this.labelExternalClock.Text = "labExtClk";
            // 
            // label_Current_Value
            // 
            this.label_Current_Value.AutoSize = true;
            this.label_Current_Value.Location = new System.Drawing.Point(163, 117);
            this.label_Current_Value.Name = "label_Current_Value";
            this.label_Current_Value.Size = new System.Drawing.Size(19, 13);
            this.label_Current_Value.TabIndex = 2227;
            this.label_Current_Value.Text = "75";
            // 
            // CyConfigurationTab
            // 
            this.AutoScroll = true;
            this.Controls.Add(this.label_Current_Value);
            this.Controls.Add(this.cbDisablesAutoBattery);
            this.Controls.Add(this.cbExternalClock);
            this.Controls.Add(this.label_exClockSrc);
            this.Controls.Add(this.pictureB_schema);
            this.Controls.Add(this.cbInputVol);
            this.Controls.Add(this.updown_outCurrent);
            this.Controls.Add(this.label_Current);
            this.Controls.Add(this.label_outCurrent);
            this.Controls.Add(this.cbSwFreq);
            this.Controls.Add(this.label_Freq);
            this.Controls.Add(this.cbOutputVol);
            this.Controls.Add(this.label_vOut);
            this.Controls.Add(this.label_vBatIn);
            this.Controls.Add(this.labelExternalClock);
            this.Controls.Add(this.labelSwFreq);
            this.Name = "CyConfigurationTab";
            this.Size = new System.Drawing.Size(577, 280);
            ((System.ComponentModel.ISupportInitialize)(this.updown_outCurrent)).EndInit();
            ((System.ComponentModel.ISupportInitialize)(this.pictureB_schema)).EndInit();
            ((System.ComponentModel.ISupportInitialize)(this.errorProvider)).EndInit();
            this.ResumeLayout(false);
            this.PerformLayout();

        }
        #endregion
    }
}
