/*******************************************************************************
* Copyright 2008-2014, Cypress Semiconductor Corporation. All rights reserved.
* You may use this file only in accordance with the license, terms, conditions, 
* disclaimers, and limitations in the end user license agreement accompanying 
* the software package with which this file was provided.
********************************************************************************/

using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Drawing;
using System.Diagnostics;
using System.Windows.Forms;
using CyDesigner.Extensions.Gde;

namespace PWM_v3_30
{
    public partial class CyConfigureTab : CyTabWrapper
    {
        #region Properties
        public override string TabName
        {
            get { return CyCustomizer.CONFIGURE_TAB_NAME; }
        }
        #endregion

        #region Constants
        private const int PB_PWMTEXT_WIDTH = 40;
        private const int PB_EXTENTS_BORDER = 5;
        private const int PB_POLYGON_WIDTH = 4;
        private const UInt16 DEFAULT_DEAD_TIME = 1;
        private const UInt16 DEFAULT_PERIOD = 255;
        private const UInt16 DEFAULT_COMPARE_VALUE_1 = 127;
        private const UInt16 DEFAULT_COMPARE_VALUE_2 = 67;
        private const string CLOCK_TERMINAL_NAME = "clock";
        private const string INTERNAL_CLOCK_TERMINAL_NAME = "or_clk";
        private const string S = "s";
        private const string MS = "ms";
        private const string US = "us";
        private const string NS = "ns";
        private const string PS = "ps";
        private const string PWM = "pwm";
        private const string PWM1 = "pwm1";
        private const string PWM2 = "pwm2";
        private const string PH1 = "ph1";
        private const string PH2 = "ph2";
        #endregion

        #region Variables
        public CyAdvancedTab m_advancedTab;
        private int m_enableModeIndex;
        private int m_runModeIndex;
        private int m_triggerModeIndex;
        private int m_killModeIndex;
        private int m_captureModeIndex;
        private int m_pwmModeIndex;
        #endregion

        #region Constructor(s)
        public CyConfigureTab(CyParameters parameters)
            : base(parameters)
        {
            this.m_params = parameters;
            m_advancedTab = null;
            InitializeComponent();
            InitializeGUIControls();

            // Declaration of NumericUpDown events
            m_numPeriod.TextChanged += m_numPeriod_TextChanged;
            m_numCompare1.TextChanged += m_numCompareValue_TextChanged;
            m_numCompare2.TextChanged += m_numCompareValue_TextChanged;
            m_numDeadBandCounts.TextChanged += m_numDeadBandCounts_TextChanged;
        }
        #endregion

        #region Form initialization
        protected void InitializeGUIControls()
        {
            m_cbPWMMode.DataSource = new List<string>(m_params.PwmMode.EnumDescriptionsList);
            m_cbCompareType1.DataSource = new List<string>(m_params.CompareType1.EnumDescriptionsList);
            m_cbCompareType2.DataSource = new List<string>(m_params.CompareType2.EnumDescriptionsList);
            m_cbDeadBandMode.DataSource = new List<string>(m_params.DeadBand.EnumDescriptionsList);
            m_cbDitherOffset.DataSource = new List<string>(m_params.DitherOffset.EnumDescriptionsList);

            m_cbDitherAlign.Items.Add(CyParameters.GetEnumDesc(CyEDitherAlign.LeftAligned));
            m_cbDitherAlign.Items.Add(CyParameters.GetEnumDesc(CyEDitherAlign.RightAligned));

            m_cbFFDeadBandMode.Items.Add(Resources.DeadBandDisabledItem);
            m_cbFFDeadBandMode.Items.Add(Resources.DeadBandCountsItem);
            m_cbFFDeadBandMode.SelectedIndex = 0;
            SetVisible(m_cbFFDeadBandMode, false);

            m_numPeriod.Minimum = CyParamRanges.PERIODMIN;
            m_numPeriod.Maximum = Decimal.MaxValue;
            m_numCompare1.Minimum = CyParamRanges.PERIODMIN;
            m_numCompare1.Maximum = Decimal.MaxValue;
            m_numCompare2.Minimum = CyParamRanges.PERIODMIN;
            m_numCompare2.Maximum = Decimal.MaxValue;
            m_numDeadBandCounts.Minimum = Decimal.MinValue;
            m_numDeadBandCounts.Maximum = Decimal.MaxValue;
        }
        #endregion

        #region Form updating routines
        public void UpdateFormFromParams()
        {
            m_cbPWMMode.SelectedItem = m_params.PwmMode.Description;

            m_cbPWMMode.Enabled = m_params.FixedFunction;

            switch (m_params.Resolution)
            {
                case CyEResolution.B_PWM__R8:
                    m_rbResolution8.Checked = true;
                    break;
                case CyEResolution.B_PWM__R16:
                    m_rbResolution16.Checked = true;
                    break;
                default:
                    m_rbResolution8.Checked = true;
                    break;
            }

            // Set the Period Numeric Up/Down
            m_numPeriod.Text = m_params.Period.ToString();

            //Set the Compare value Numeric Up/Downs
            m_numCompare1.Text = m_params.CompareValue1.ToString();
            m_numCompare2.Text = m_params.CompareValue2.ToString();

            // Set the Compare Type and Dither Combo Boxes
            m_cbDitherAlign.SelectedItem = CyParameters.GetEnumDesc(m_params.DitherAlign);

            //Set the Dither Offset Combo Box
            m_cbDitherOffset.SelectedItem = m_params.DitherOffset.Description;

            //Set the CompareType1 Offset Combo Box
            m_cbCompareType1.SelectedItem = m_params.CompareType1.Description;

            //Set the CompareType2 Offset Combo Box
            m_cbCompareType2.SelectedItem = m_params.CompareType2.Description;

            //Set the Dead Band Mode Combo Box
            m_cbDeadBandMode.SelectedItem = m_params.DeadBand.Description;
            m_cbFFDeadBandMode.SelectedIndex = (m_params.DeadBand.Value == CyEDeadBandMode.B_PWM__DBMDisabled) ? 0 : 1;

            if (m_params.FixedFunction)
            {
                m_rbFixedFunction.Checked = true;
                SetFixedFunction();
                m_numDeadBandCounts.Text = m_params.DeadTime.ToString();
            }
            else
            {
                m_rbUDB.Checked = true;
                ClearFixedFunction();
                m_numDeadBandCounts.Text = (m_params.DeadTime + 1).ToString();
            }

            SetFrequencyLabel(m_params.Period);
            UpdateDrawing();
            SetControlVisibilityFromMode();
            SetControlVisibilityCompareType();
        }
        #endregion

        #region Control event handlers
        void m_numPeriod_TextChanged(object sender, EventArgs e)
        {
            m_params.Period = ValidatePeriod();
            // Update error providers of CMP values.
            ValidateCompareValue(m_numCompare1);
            ValidateCompareValue(m_numCompare2);
            SetFrequencyLabel(m_params.Period);
            UpdateDrawing();
        }

        private void m_cbPWMMode_SelectedIndexChanged(object sender, EventArgs e)
        {
            m_params.PwmMode.Description = m_cbPWMMode.Text;
            SetControlVisibilityCompareType();

            // Extracted this from SetControlVisibilityCompareType
            if (m_params.PwmMode.Value == CyEPwmMode.B_PWM__Dither)
            {
                UInt16 compareValue1;
                if (UInt16.TryParse(m_numCompare1.Text, out compareValue1))
                {
                    m_params.CompareValue2 = (UInt16)(compareValue1 + 1);
                    m_numCompare2.Text = m_params.CompareValue2.ToString();
                }
            }

            // If invalid CMP 2 value was input and then user switched to the "One output" mode,
            // the CPM 2 value will be set to the maximum available Period value since CMP 2 controls
            // are hidden in this mode.
            if (m_params.PwmMode.Value == CyEPwmMode.B_PWM__One_Output)
            {
                if (String.IsNullOrEmpty(m_errorProvider.GetError(m_numCompare2)) == false)
                {
                    m_numCompare2.Text = m_params.GetPeriodMaxValue().ToString();
                    m_errorProvider.SetError(m_numCompare2, String.Empty);
                }
            }

            SetFrequencyLabel(m_params.Period);
            ValidatePeriod();
            ValidateCompareValue(m_numCompare1);
            ValidateCompareValue(m_numCompare2);
            UpdateDrawing();
        }

        void m_numCompareValue_TextChanged(object sender, EventArgs e)
        {
            UInt16? compareValue = ValidateCompareValue((NumericUpDown)sender);

            if (sender == m_numCompare1)
            {
                m_params.CompareValue1 = compareValue;
            }
            if (sender == m_numCompare2)
            {
                m_params.CompareValue2 = compareValue;
            }

            if (compareValue.HasValue)
                UpdateDrawing();
        }

        private void m_cbCompareType1_SelectedIndexChanged(object sender, EventArgs e)
        {
            m_params.CompareType1.Description = m_cbCompareType1.Text;
            ValidateCompareType1();

            UpdateDrawing();
        }

        private void m_cbCompareType2_SelectedIndexChanged(object sender, EventArgs e)
        {
            m_params.CompareType2.Description = m_cbCompareType2.Text;
            UpdateDrawing();
        }

        private void m_rbResolution_CheckedChanged(object sender, EventArgs e)
        {
            if (((RadioButton)sender).Checked)
            {
                m_params.Resolution = (m_rbResolution8.Checked) ? CyEResolution.B_PWM__R8 : CyEResolution.B_PWM__R16;
                UpdateDrawing();

                // Validate depending controls
                UInt16? period = ValidatePeriod();
                if (m_rbResolution16.Checked)
                {
                    m_params.Period = period;
                }
                ValidateCompareValue(m_numCompare1);
                ValidateCompareValue(m_numCompare2);
            }
        }

        private void m_cbDitherAlign_SelectedIndexChanged(object sender, EventArgs e)
        {
            if (m_params.PwmMode.Value == CyEPwmMode.B_PWM__Dither)
            {
                if (m_cbDitherAlign.Text == CyParameters.GetEnumDesc(CyEDitherAlign.LeftAligned))
                {
                    m_params.CompareType1.Value = CyECompareType.B_PWM__Greater_Than_Or_Equal_To;
                    m_params.CompareType2.Value = CyECompareType.B_PWM__Greater_Than_Or_Equal_To;
                }
                else // Right Aligned
                {
                    m_params.CompareType1.Value = CyECompareType.B_PWM__Less_Than_Or_Equal;
                    m_params.CompareType2.Value = CyECompareType.B_PWM__Less_Than_Or_Equal;
                }
                UpdateDrawing();
            }
        }

        private void m_cbDitherOffset_SelectedIndexChanged(object sender, EventArgs e)
        {
            m_params.DitherOffset.Description = m_cbDitherOffset.Text;
            UpdateDrawing();
        }

        private void m_cbDeadBandMode_SelectedIndexChanged(object sender, EventArgs e)
        {
            m_params.DeadBand.Description = m_cbDeadBandMode.Text;

            if (IsControlHidden(m_cbDeadBandMode) == false)
            {
                if (m_params.DeadBand.Value == CyEDeadBandMode.B_PWM__DBMDisabled)
                {
                    m_numDeadBandCounts.Enabled = false;
                }
                else if (m_params.DeadBand.Value == CyEDeadBandMode.B_PWM__DBM_2_4_Clocks)
                {
                    m_numDeadBandCounts.Enabled = true;
                }
                else if (m_params.FixedFunction == false)
                {
                    m_numDeadBandCounts.Enabled = true;
                }
            }

            UpdateDrawing();
            ValidateCompareType1();
            ValidateDeadBandCounts();
        }

        private void m_numDeadBandCounts_TextChanged(object sender, EventArgs e)
        {
            UInt16? deadBandCounts = ValidateDeadBandCounts();
            if (deadBandCounts.HasValue)
            {
                if (m_cbDeadBandMode.Enabled)
                    m_params.DeadTime = (byte)(deadBandCounts.Value - 1);
                else
                    m_params.DeadTime = (byte)deadBandCounts.Value;
            }
            UpdateDrawing();
        }

        private void m_cbFFDeadBandMode_SelectedIndexChanged(object sender, EventArgs e)
        {
            if (IsControlHidden(m_cbFFDeadBandMode) == false)
            {
                m_numDeadBandCounts.Enabled = (m_cbFFDeadBandMode.SelectedIndex != 0); // not equal Disabled
            }

            if (m_cbFFDeadBandMode.SelectedIndex == 0)
            {
                m_params.DeadBand.Value = CyEDeadBandMode.B_PWM__DBMDisabled;
            }
            else
            {
                m_params.DeadBand.Value = CyEDeadBandMode.B_PWM__DBM_2_4_Clocks;
            }
            ValidateCompareType1();
            ValidateDeadBandCounts();
            UpdateDrawing();
        }

        private void m_rbFixedFunction_CheckedChanged(object sender, EventArgs e)
        {
            if (((RadioButton)sender).Checked == false || m_params.GlobalEditMode == false) return;

            m_params.FixedFunction = true;

            m_enableModeIndex = m_advancedTab.m_cbEnableMode.SelectedIndex;
            m_runModeIndex = m_advancedTab.m_cbRunMode.SelectedIndex;
            m_triggerModeIndex = m_advancedTab.m_cbTriggerMode.SelectedIndex;
            m_killModeIndex = m_advancedTab.m_cbKillMode.SelectedIndex;
            m_captureModeIndex = m_advancedTab.m_cbCaptureMode.SelectedIndex;
            m_pwmModeIndex = m_cbPWMMode.SelectedIndex;

            if (m_advancedTab != null)
            {
                m_advancedTab.SetFixedFunction();

            }
        }

        private void m_rbUDB_CheckedChanged(object sender, EventArgs e)
        {
            if (((RadioButton)sender).Checked == false || m_params.GlobalEditMode == false) return;

            m_params.FixedFunction = false;

            m_advancedTab.m_cbEnableMode.SelectedIndex = m_enableModeIndex;
            m_advancedTab.m_cbRunMode.SelectedIndex = m_runModeIndex;
            m_advancedTab.m_cbTriggerMode.SelectedIndex = m_triggerModeIndex;
            m_advancedTab.m_cbKillMode.SelectedIndex = m_killModeIndex;
            m_advancedTab.m_cbCaptureMode.SelectedIndex = m_captureModeIndex;
            m_cbPWMMode.SelectedIndex = m_pwmModeIndex;

            if (m_advancedTab != null)
            {
                m_advancedTab.ClearFixedFunction();
            }
        }

        private void m_bMaxPeriod_Click(object sender, EventArgs e)
        {
            m_numPeriod.Text = m_params.GetPeriodMaxValue().ToString();
        }

        private void CyPWMControl_SizeChanged(object sender, EventArgs e)
        {
            UpdateDrawing();
        }

        private void CyPWMControl_Load(object sender, EventArgs e)
        {
            if (m_params.DeviceQuery.IsPSoC4)
            {
                SetVisible(m_rbFixedFunction, false);
                m_rbUDB.Left = m_rbFixedFunction.Left;
                m_rbUDB.Top = m_rbFixedFunction.Top;
                m_rbUDB.Checked = true;
                m_rbUDB.Enabled = false;
                m_params.FixedFunction = false;
            }
        }
        #endregion

        #region Switching between FixedFunction and UDB
        private void SetFixedFunction()
        {
            // Hide all of the fixed function block limitations
            m_params.PwmMode.Value = CyEPwmMode.B_PWM__One_Output;
            m_cbPWMMode.SelectedItem = m_params.PwmMode.Description;
            m_cbPWMMode.Enabled = false;
            if (m_cbDeadBandMode.SelectedIndex == 0)
            {
                m_params.DeadBand.Description = m_cbFFDeadBandMode.SelectedItem.ToString();
                m_cbFFDeadBandMode.SelectedIndex = 0;
            }
            m_cbDeadBandMode.Enabled = false;
            SetVisible(m_cbDeadBandMode, false);
            SetVisible(m_cbFFDeadBandMode, true);
            SetVisible(m_cbDeadBandMode, false);

            if (m_params.DeadBand.Value == CyEDeadBandMode.B_PWM__DBMDisabled)
            {
                m_numDeadBandCounts.Enabled = false;
            }
            else
            {
                ValidateCompareType1();
                m_numDeadBandCounts.Enabled = true;
            }           
            ValidateDeadBandCounts();
        }

        private void ClearFixedFunction()
        {
            m_cbPWMMode.Enabled = true;
            m_cbDeadBandMode.Enabled = true;
            SetVisible(m_cbFFDeadBandMode, false);
            SetVisible(m_cbDeadBandMode, true);
            if (m_params.DeadBand.Value == CyEDeadBandMode.B_PWM__DBMDisabled)
                m_numDeadBandCounts.Enabled = false;
            else
            {
                ValidateCompareType1();
                m_numDeadBandCounts.Enabled = true;
            }
            ValidateDeadBandCounts();
        }
        #endregion

        #region Clock update
        public void UpdateClock(ICyInstQuery_v1 edit, ICyTerminalQuery_v1 termQuery)
        {
            UInt16 period;

            try
            {
                period = Convert.ToUInt16(m_numPeriod.Value);
            }
            catch (OverflowException ex)
            {
                Debug.Fail(ex.Message);
                period = UInt16.MaxValue;
            }

            SetFrequencyLabel(period);
        }

        private void SetFrequencyLabel(int? period)
        {
            if (period.HasValue == false) return; // Exit if period is invalid

            List<CyClockData> clkdata = new List<CyClockData>();
            clkdata = m_params.InstQuery.IsInSystemBuilder ? 
                m_params.TermQuery.GetClockData(INTERNAL_CLOCK_TERMINAL_NAME, "term1", 0) :
                m_params.TermQuery.GetClockData(CLOCK_TERMINAL_NAME, 0);

            double infreq = 0;
            try
            {
                if (clkdata[0].IsFrequencyKnown)
                {
                    infreq = clkdata[0].Frequency * Math.Pow(10, clkdata[0].UnitAsExponent);
                }
                if (infreq > 0)
                {
                    double periodfreq = infreq / (period.Value + 1);
                    double periodtime = 1 / periodfreq;

                    int i = 0;
                    while (periodtime < 1 && i < 12) // pico seconds
                    {
                        periodtime = periodtime * 1000;
                        i += 3;
                    }
                    if (m_params.PwmMode.Value == CyEPwmMode.B_PWM__Center_Align)
                    {
                        periodtime = periodtime * 2;
                    }
                    string time = "s";
                    switch (i)
                    {
                        case 0: time = S; break;
                        case 3: time = MS; break;
                        case 6: time = US; break;
                        case 9: time = NS; break;
                        case 12: time = PS; break;
                    }
                    m_lblCalcFrequency.Text = String.Format(Resources.FrequencyLabel, Math.Round(periodtime, 3), time);
                    //Set the Tooltip m_lblCalcFrequency.To
                }
                else
                {
                    throw new Exception();
                }
            }
            catch (Exception)
            {
                m_lblCalcFrequency.Text = Resources.UnknownFrequencyLabel;
            }
        }
        #endregion

        #region Validators
        // Period
        private UInt16? ValidatePeriod()
        {
            string errorMessage = String.Empty;
            UInt16 periodValue = DEFAULT_PERIOD;
            UInt16 min = CyParamRanges.PERIODMIN;
            Decimal max = m_params.GetPeriodMaxValue();

            try
            {
                periodValue = Convert.ToUInt16(m_numPeriod.Text);

                if (periodValue < min || periodValue > max)
                {
                    errorMessage = String.Format(Resources.PeriodOutOfRange, min, max);
                }
            }
            catch (OverflowException)
            {
                errorMessage = String.Format(Resources.ValueOutOfUInt16Range, m_numPeriod.Text);
            }
            catch (FormatException)
            {
                errorMessage = String.Format(Resources.ValueNotInRecognizableFormat, m_numPeriod.Text);
            }

            m_errorProvider.SetError(m_numPeriod, errorMessage);

            return (String.IsNullOrEmpty(errorMessage)) ? periodValue : (UInt16?)null;
        }

        // Compare value
        private UInt16? ValidateCompareValue(NumericUpDown numericUpDownControl)
        {
            string errorMessage = String.Empty;
            UInt16? compareValue = null;
            Decimal min = CyParamRanges.PERIODMIN;
            Decimal max = (m_params.Period.HasValue) ? m_params.Period.Value :
                ((m_params.Resolution == CyEResolution.B_PWM__R8) ?
                CyParamRanges.PERIODMAX8 : CyParamRanges.PERIODMAX16);
            try
            {
                compareValue = Convert.ToUInt16(numericUpDownControl.Text);
            }
            catch (OverflowException)
            {
                errorMessage = String.Format(Resources.CompareValueOutOfRange, min, max);
            }
            catch (FormatException)
            {
                errorMessage = String.Format(Resources.ValueNotInRecognizableFormat, numericUpDownControl.Text);
            }

            if (compareValue.HasValue)
            {
                if (compareValue < min || compareValue > max)
                {
                    errorMessage = String.Format(Resources.CompareValueOutOfRange, min, max);
                }
            }

            m_errorProvider.SetError(numericUpDownControl, errorMessage);

            return compareValue;
        }

        // DeadBand counts
        UInt16? ValidateDeadBandCounts()
        {
            string errorMessage = String.Empty;
            UInt16? deadTime = null;
            Decimal min;
            Decimal max;
            try
            {
                deadTime = Convert.ToUInt16(m_numDeadBandCounts.Text);
            }
            catch { }

            if (m_params.FixedFunction)
            {
                min = CyParamRanges.DEADBANDFFCOUNTS_MIN;
                max = CyParamRanges.DEADBANDFFCOUNTS_MAX;
                errorMessage = String.Format(Resources.DeadBandFFCountsOutOfRange, min, max);
            }
            else
            {
                if (m_params.DeadBand.Value == CyEDeadBandMode.B_PWM__DBM_2_4_Clocks)
                {
                    min = CyParamRanges.DEADBANDCOUNTS_MIN;
                    max = CyParamRanges.DEADBANDCOUNTS_4MAX;
                    errorMessage = String.Format(Resources.DeadBandCountsOutOfRange, min, max);
                }
                else
                {
                    min = CyParamRanges.DEADBANDCOUNTS_MIN;
                    max = CyParamRanges.DEADBANDCOUNTS_256MAX;
                    errorMessage = String.Format(Resources.DeadBandCountsOutOfRange, min, max);
                }
            }

            if (deadTime.HasValue)
            {
                if (deadTime.Value >= min && deadTime.Value <= max)
                {
                    errorMessage = String.Empty;
                }
            }
            if (m_numDeadBandCounts.Enabled == false)
            {
                errorMessage = String.Empty;
            }

            m_errorProvider.SetError(m_numDeadBandCounts, errorMessage);

            return deadTime;
        }

        // Compare type
        bool ValidateCompareType1()
        {
            string errorMessage = String.Empty;
            if (m_params.CompareType1.Value == CyECompareType.B_PWM__Equal &&
                m_params.DeadBand.Value != CyEDeadBandMode.B_PWM__DBMDisabled)
            {
                errorMessage = Resources.CompareType1NotSupportedForDeadBand;
            }
            m_errorProvider.SetError(m_cbCompareType1, errorMessage);
            return String.IsNullOrEmpty(errorMessage);
        }
        #endregion

        #region Control appearance
        private void SetControlVisibilityFromMode()
        {
            if (m_params.PwmMode.Value == CyEPwmMode.B_PWM__Dither)
            {
                SetVisible(m_cbDitherAlign, true);
                SetVisible(m_cbCompareType1, false);
                SetVisible(m_cbDitherOffset, true);
            }
            else
            {
                SetVisible(m_cbDitherAlign, false);
                SetVisible(m_cbCompareType1, true);
                SetVisible(m_cbDitherOffset, false);
            }

            if (m_params.PwmMode.Value == CyEPwmMode.B_PWM__One_Output ||
                m_params.PwmMode.Value == CyEPwmMode.B_PWM__Center_Align)
            {
                SetVisible(m_cbCompareType2, false);
                SetVisible(m_numCompare2, false);
                SetVisible(m_lblCmpType2, false);
                SetVisible(m_lblCmpValue2, false);
            }
            else
            {
                SetVisible(m_cbCompareType2, true);
                SetVisible(m_numCompare2, true);
                SetVisible(m_lblCmpType2, true);
                SetVisible(m_lblCmpValue2, true);
            }
            UInt16 tmp2 = (m_params.Period.HasValue) ? m_params.Period.Value : DEFAULT_PERIOD;
            SetFrequencyLabel(tmp2);
        }

        private void SetControlVisibilityCompareType()
        {
            if (m_params.PwmMode.Value == CyEPwmMode.B_PWM__Two_Outputs ||
                m_params.PwmMode.Value == CyEPwmMode.B_PWM__Dual_Edge ||
                m_params.PwmMode.Value == CyEPwmMode.B_PWM__HardwareSelect)
            {
                SetVisible(m_numCompare2, true);
                SetVisible(m_lblCmpValue2, true);
                SetVisible(m_lblCmpType2, true);
                SetVisible(m_cbCompareType2, true);
                SetVisible(m_cbDitherOffset, false);
                SetVisible(m_cbDitherAlign, false);
                SetVisible(m_cbCompareType1, true);
                m_lblCmpType1.Text = Resources.CmpType1Label;
            }
            else if (m_params.PwmMode.Value == CyEPwmMode.B_PWM__One_Output ||
                     m_params.PwmMode.Value == CyEPwmMode.B_PWM__Center_Align)
            {
                SetVisible(m_numCompare2, false);
                SetVisible(m_lblCmpValue2, false);
                SetVisible(m_lblCmpType2, false);
                SetVisible(m_cbCompareType2, false);
                SetVisible(m_cbDitherOffset, false);
                SetVisible(m_cbDitherAlign, false);
                SetVisible(m_cbCompareType1, true);
                m_lblCmpType1.Text = Resources.CmpType1Label;
            }
            else if (m_params.PwmMode.Value == CyEPwmMode.B_PWM__Dither)
            {
                SetVisible(m_numCompare2, false);
                SetVisible(m_lblCmpValue2, false);
                SetVisible(m_lblCmpType2, false);
                SetVisible(m_cbCompareType2, false);
                SetVisible(m_cbDitherOffset, true);
                SetVisible(m_cbDitherAlign, true);
                SetVisible(m_cbCompareType1, false);
                m_lblCmpType1.Text = Resources.CmpType1LabelAlignment;
            }
        }
        #endregion

        #region Drawing
        /// <summary>
        /// Initializes array PointF elements that are in range of fromIndex and toIndex with PointF value 
        /// passed as argument
        /// </summary>
        /// <param name="ptsArray">Array to initialize</param>
        /// <param name="fromIndex">Start index</param>
        /// <param name="toIndex">End index</param>
        /// <param name="point">Value to assign to the array elements</param>
        private void InitializePointArray(PointF[] ptsArray, int fromIndex, int toIndex, PointF point)
        {
            for (int i = fromIndex; i <= toIndex; i++)
            {
                ptsArray[i] = point;
            }
        }

        public void UpdateDrawing()
        {
            // Do not update diagram if any of controls contain invalid data.
            if (CheckControlForErrors(this.Controls).Count > 0) return;

            #region Setup Waveform with Extents and Cushions etc
            CancelEventArgs ce = new CancelEventArgs();
            if (ValidatePeriod().HasValue == false) return;
            if (ValidateCompareValue(m_numCompare1).HasValue == false) return;
            if (IsControlHidden(m_numCompare2) == false)
            {
                if (ValidateCompareValue(m_numCompare2).HasValue == false) return;
            }
            if (m_numDeadBandCounts.Enabled)
            {
                if (ValidateDeadBandCounts().HasValue == false) return;
            }
            if ((m_pbDrawing.Width == 0) || (m_pbDrawing.Height == 0))
                return;
            Image waveform = new Bitmap(m_pbDrawing.Width, m_pbDrawing.Height);
            Graphics wfg;
            wfg = Graphics.FromImage(waveform);
            wfg.Clear(Color.White);
            SolidBrush blkbrush = new SolidBrush(Color.Black);
            SolidBrush whitebrush = new SolidBrush(Color.White);
            SolidBrush greybrush = new SolidBrush(Color.LightGray);
            SolidBrush redbrush = new SolidBrush(Color.FromArgb(120, Color.Red));


            float extentsleft = PB_EXTENTS_BORDER + PB_PWMTEXT_WIDTH;
            float extentsright = m_pbDrawing.Width - PB_EXTENTS_BORDER;
            float padding = (extentsright - extentsleft) / 70;
            float startleft = extentsleft + padding;
            float endright = extentsright - padding;
            float startright = startleft + (endright - startleft) / 2;
            float cacenter1 = startleft + (startright - startleft) / 2;
            float cacenter2 = startright + (endright - startright) / 2;

            //Setup the right, left and center indicators
            Pen extentspen = new Pen(blkbrush);
            extentspen.DashStyle = System.Drawing.Drawing2D.DashStyle.Dash;
            //Draw the Left Extents Line
            wfg.DrawLine(extentspen, extentsleft, PB_EXTENTS_BORDER,
                extentsleft, m_pbDrawing.Height - PB_EXTENTS_BORDER);
            //Draw the Right Extents Line
            wfg.DrawLine(extentspen, extentsright, PB_EXTENTS_BORDER,
                extentsright, m_pbDrawing.Height - PB_EXTENTS_BORDER);
            //Draw the Left Start line
            wfg.DrawLine(extentspen, startleft, PB_EXTENTS_BORDER,
                startleft, m_pbDrawing.Height - PB_EXTENTS_BORDER);
            //Draw the Right Start Line
            wfg.DrawLine(extentspen, startright, PB_EXTENTS_BORDER,
                startright, m_pbDrawing.Height - PB_EXTENTS_BORDER);
            //Draw the Right End Line
            wfg.DrawLine(extentspen, endright, PB_EXTENTS_BORDER,
                endright, m_pbDrawing.Height - PB_EXTENTS_BORDER);
            //Fill the Left Padding Rectangle
            greybrush.Color = Color.FromArgb(100, Color.LightGray);
            wfg.FillRectangle(greybrush,
                extentsleft, PB_EXTENTS_BORDER, padding, m_pbDrawing.Height - PB_EXTENTS_BORDER);
            //Fill the Right Padding Rectangle
            wfg.FillRectangle(greybrush,
                endright, PB_EXTENTS_BORDER, padding, m_pbDrawing.Height - PB_EXTENTS_BORDER);

            if (m_params.PwmMode.Value == CyEPwmMode.B_PWM__Center_Align)
            {
                wfg.DrawLine(extentspen, cacenter1, PB_EXTENTS_BORDER,
                cacenter1, m_pbDrawing.Height - PB_EXTENTS_BORDER);
                wfg.DrawLine(extentspen, cacenter2, PB_EXTENTS_BORDER,
                cacenter2, m_pbDrawing.Height - PB_EXTENTS_BORDER);
            }
            extentspen.Dispose();

            //Draw the Line with the Period Value
            Pen periodspen = new Pen(blkbrush);
            wfg.DrawLine(periodspen, startleft, PB_EXTENTS_BORDER + PB_POLYGON_WIDTH,
                endright, PB_EXTENTS_BORDER + PB_POLYGON_WIDTH);

            //Draw the Left Side Left Arrow
            PointF[] arrowpts = new PointF[3];
            arrowpts[0] = new PointF(startleft, PB_EXTENTS_BORDER + PB_POLYGON_WIDTH);
            arrowpts[1] = new PointF(startleft + PB_POLYGON_WIDTH, PB_EXTENTS_BORDER);
            arrowpts[2] = new PointF(startleft + PB_POLYGON_WIDTH,
                PB_EXTENTS_BORDER + (2 * PB_POLYGON_WIDTH));
            wfg.FillPolygon(blkbrush, arrowpts);

            //Draw the Right Side Left Arrow
            arrowpts[0] = new PointF(startright, PB_EXTENTS_BORDER + PB_POLYGON_WIDTH);
            arrowpts[1] = new PointF(startright + PB_POLYGON_WIDTH, PB_EXTENTS_BORDER);
            arrowpts[2] = new PointF(startright + PB_POLYGON_WIDTH,
                PB_EXTENTS_BORDER + (2 * PB_POLYGON_WIDTH));
            wfg.FillPolygon(blkbrush, arrowpts);

            //Draw the Left Side Right Arrow
            arrowpts[0] = new PointF(startright, PB_EXTENTS_BORDER + PB_POLYGON_WIDTH);
            arrowpts[1] = new PointF(startright - PB_POLYGON_WIDTH, PB_EXTENTS_BORDER);
            arrowpts[2] = new PointF(startright - PB_POLYGON_WIDTH,
                PB_EXTENTS_BORDER + (2 * PB_POLYGON_WIDTH));
            wfg.FillPolygon(blkbrush, arrowpts);

            //Draw the Right Side Right Arrow
            arrowpts[0] = new PointF(endright, PB_EXTENTS_BORDER + PB_POLYGON_WIDTH);
            arrowpts[1] = new PointF(endright - PB_POLYGON_WIDTH, PB_EXTENTS_BORDER);
            arrowpts[2] = new PointF(endright - PB_POLYGON_WIDTH,
                PB_EXTENTS_BORDER + (2 * PB_POLYGON_WIDTH));
            wfg.FillPolygon(blkbrush, arrowpts);

            if (m_params.PwmMode.Value == CyEPwmMode.B_PWM__Center_Align)
            {
                arrowpts[0] = new PointF(cacenter1, PB_EXTENTS_BORDER + PB_POLYGON_WIDTH);
                arrowpts[1] = new PointF(cacenter1 - PB_POLYGON_WIDTH, PB_EXTENTS_BORDER);
                arrowpts[2] = new PointF(cacenter1 - PB_POLYGON_WIDTH,
                    PB_EXTENTS_BORDER + (2 * PB_POLYGON_WIDTH));
                wfg.FillPolygon(blkbrush, arrowpts);
                arrowpts[0] = new PointF(cacenter1, PB_EXTENTS_BORDER + PB_POLYGON_WIDTH);
                arrowpts[1] = new PointF(cacenter1 + PB_POLYGON_WIDTH, PB_EXTENTS_BORDER);
                arrowpts[2] = new PointF(cacenter1 + PB_POLYGON_WIDTH,
                    PB_EXTENTS_BORDER + (2 * PB_POLYGON_WIDTH));
                wfg.FillPolygon(blkbrush, arrowpts);
                arrowpts[0] = new PointF(cacenter2, PB_EXTENTS_BORDER + PB_POLYGON_WIDTH);
                arrowpts[1] = new PointF(cacenter2 - PB_POLYGON_WIDTH, PB_EXTENTS_BORDER);
                arrowpts[2] = new PointF(cacenter2 - PB_POLYGON_WIDTH,
                    PB_EXTENTS_BORDER + (2 * PB_POLYGON_WIDTH));
                wfg.FillPolygon(blkbrush, arrowpts);
                arrowpts[0] = new PointF(cacenter2, PB_EXTENTS_BORDER + PB_POLYGON_WIDTH);
                arrowpts[1] = new PointF(cacenter2 + PB_POLYGON_WIDTH, PB_EXTENTS_BORDER);
                arrowpts[2] = new PointF(cacenter2 + PB_POLYGON_WIDTH,
                    PB_EXTENTS_BORDER + (2 * PB_POLYGON_WIDTH));
                wfg.FillPolygon(blkbrush, arrowpts);
            }

            //Draw the Period Name String
            Font perfont = new Font("Arial", 10, FontStyle.Regular, GraphicsUnit.Pixel);
            wfg.DrawString("period", perfont, blkbrush,
                            new PointF(PB_PWMTEXT_WIDTH - wfg.MeasureString("Period", perfont).Width,
                PB_EXTENTS_BORDER + PB_POLYGON_WIDTH - (wfg.MeasureString("period", perfont).Height / 2)));

            //Draw the Period Text at the start and at the end of the waveform
            string periodStr = m_params.Period.ToString();
            if (m_params.PwmMode.Value != CyEPwmMode.B_PWM__Center_Align)
            {

                //Draw the Period Values at the Left
                SizeF pervalsize = wfg.MeasureString(periodStr, perfont);
                RectangleF pervalrect1 = new RectangleF(startleft + (2 * PB_POLYGON_WIDTH),
                    PB_EXTENTS_BORDER + PB_POLYGON_WIDTH - (pervalsize.Height / 2),
                    pervalsize.Width, pervalsize.Height);
                wfg.FillRectangle(whitebrush, pervalrect1);
                wfg.DrawString(periodStr, perfont, blkbrush, pervalrect1);

                RectangleF pervalrect2 = new RectangleF(startright + (2 * PB_POLYGON_WIDTH),
                    PB_EXTENTS_BORDER + PB_POLYGON_WIDTH - (pervalsize.Height / 2),
                    pervalsize.Width, pervalsize.Height);
                wfg.FillRectangle(whitebrush, pervalrect2);
                wfg.DrawString(periodStr, perfont, blkbrush, pervalrect2);

                //Draw the zero Values at the Right
                SizeF perzerosize = wfg.MeasureString("0", perfont);
                RectangleF perzerorect1 = new RectangleF(startright - (2 * PB_POLYGON_WIDTH) - perzerosize.Width,
                    PB_EXTENTS_BORDER + PB_POLYGON_WIDTH - (perzerosize.Height / 2), perzerosize.Width,
                    perzerosize.Height);
                wfg.FillRectangle(whitebrush, perzerorect1);
                wfg.DrawString("0", perfont, blkbrush, perzerorect1);

                RectangleF perzerorect2 = new RectangleF(endright - (2 * PB_POLYGON_WIDTH) - perzerosize.Width,
                    PB_EXTENTS_BORDER + PB_POLYGON_WIDTH - (perzerosize.Height / 2), perzerosize.Width,
                    perzerosize.Height);
                wfg.FillRectangle(whitebrush, perzerorect2);
                wfg.DrawString("0", perfont, blkbrush, perzerorect2);
            }
            else
            {
                //If Center Aligned mode then count from zero up to period and then back down
                //Draw the 0 text in the three locations
                SizeF zerosize = wfg.MeasureString("0", perfont);
                RectangleF zero1rect = new RectangleF(startleft + (2 * PB_POLYGON_WIDTH),
                    PB_EXTENTS_BORDER + PB_POLYGON_WIDTH - (zerosize.Height / 2), zerosize.Width, zerosize.Height);
                wfg.FillRectangle(whitebrush, zero1rect);
                wfg.DrawString("0", perfont, blkbrush, zero1rect);

                RectangleF zero2rect = new RectangleF(startright - (2 * PB_POLYGON_WIDTH) - zerosize.Width,
                    PB_EXTENTS_BORDER + PB_POLYGON_WIDTH - (zerosize.Height / 2), zerosize.Width, zerosize.Height);
                wfg.FillRectangle(whitebrush, zero2rect);
                wfg.DrawString("0", perfont, blkbrush, zero2rect);

                RectangleF zero3rect = new RectangleF(endright - (2 * PB_POLYGON_WIDTH) - zerosize.Width,
                    PB_EXTENTS_BORDER + PB_POLYGON_WIDTH - (zerosize.Height / 2), zerosize.Width, zerosize.Height);
                wfg.FillRectangle(whitebrush, zero3rect);
                wfg.DrawString("0", perfont, blkbrush, zero3rect);

                SizeF periodsize = wfg.MeasureString(periodStr, perfont);
                RectangleF per1rect = new RectangleF(cacenter1 + (2 * PB_POLYGON_WIDTH),
                    PB_EXTENTS_BORDER + PB_POLYGON_WIDTH - (periodsize.Height / 2), periodsize.Width,
                    periodsize.Height);
                wfg.FillRectangle(whitebrush, per1rect);
                wfg.DrawString(periodStr, perfont, blkbrush, per1rect);

                RectangleF per2rect = new RectangleF(cacenter2 + (2 * PB_POLYGON_WIDTH),
                    PB_EXTENTS_BORDER + PB_POLYGON_WIDTH - (periodsize.Height / 2), periodsize.Width,
                    periodsize.Height);
                wfg.FillRectangle(whitebrush, per2rect);
                wfg.DrawString(periodStr, perfont, blkbrush, per2rect);
            }

            //setup and draw all of the waveforms
            int numwaveforms = 1;
            //Number of waveforms is dependant upon the PWM mode and Dead Band
            //If Mode = One Output
            //  If DeadBand then 3 waveforms
            //  else 1 waveform
            //Else If Mode == Two Outputs
            //  If DeadBand then 4 waveforms
            //  else 2 waveforms
            //Else (Mode == Center Aligned, Dither, or Dual Mode)
            //  If DeadBand then 2 waveforms
            //  Else 1 Waveform 
            List<string> wfnames = new List<string>();

            switch (m_params.PwmMode.Value)
            {
                case CyEPwmMode.B_PWM__One_Output:
                case CyEPwmMode.B_PWM__Center_Align:
                case CyEPwmMode.B_PWM__Dither:
                    wfnames.Add(PWM);
                    break;
                case CyEPwmMode.B_PWM__Two_Outputs:
                    wfnames.Add(PWM1);
                    wfnames.Add(PWM2);
                    break;
                case CyEPwmMode.B_PWM__Dual_Edge:
                case CyEPwmMode.B_PWM__HardwareSelect:
                    wfnames.Add(PWM1);
                    wfnames.Add(PWM2);
                    wfnames.Add(PWM);
                    break;
                default:
                    m_errorProvider.SetError(m_cbPWMMode, Resources.ErrorSettingPWMMode);
                    break;
            }

            if (m_params.DeadBand.Value != CyEDeadBandMode.B_PWM__DBMDisabled)
            {
                wfnames.Add(PH1);
                wfnames.Add(PH2);
            }

            numwaveforms = wfnames.Count;

            //Each waveform's height is dependent upon the drawing size minus a top and bottom border 
            //and the top period waveform which is the size of two polygon widths, 
            // and an bottom ticker tape of 2 polygon widths
            float wfheight = (m_pbDrawing.Height - (2 * PB_EXTENTS_BORDER) - (4 * PB_POLYGON_WIDTH)) / numwaveforms;

            //Fill in All Waveform Names
            for (int i = 0; i < numwaveforms; i++)
            {
                PointF pt = new PointF(extentsleft - wfg.MeasureString(wfnames[i], perfont).Width - PB_EXTENTS_BORDER,
                    PB_EXTENTS_BORDER + (2 * PB_POLYGON_WIDTH) + (wfheight * i) + (wfheight / 2) -
                    (wfg.MeasureString(wfnames[i], perfont).Height / 2));
                wfg.DrawString(wfnames[i], perfont, blkbrush, pt);
            }
            #endregion

            //Draw Waveforms
            bool StartHigh = false;
            float Edge1 = 0;
            float Edge1_2 = 0;
            float Edge2 = 0;
            float Edge2_2 = 0;
            float Edge3 = 0;
            float Edge3_2 = 0;
            float Edge4 = 0;
            float Edge4_2 = 0;
            float bitwidth = 0;
            Int32 PeriodValue32 = (m_params.Period.HasValue) ? m_params.Period.Value : DEFAULT_PERIOD;

            if (m_params.PwmMode.Value == CyEPwmMode.B_PWM__Center_Align)
                bitwidth = ((float)(startright - startleft) / ((float)PeriodValue32)) / 2f;
            else
                bitwidth = (float)(startright - startleft) / ((float)PeriodValue32 + 1);

            Int32 DeadTimeValue32 = m_params.DeadTime.HasValue ? m_params.DeadTime.Value : DEFAULT_DEAD_TIME;

            Int32 CompareValue32 = m_params.CompareValue1.HasValue ?
                m_params.CompareValue1.Value : DEFAULT_COMPARE_VALUE_1;

            Int32 Compare2Value32 = m_params.CompareValue2.HasValue ?
                m_params.CompareValue2.Value : DEFAULT_COMPARE_VALUE_2;

            UInt16 Compare1Value16 = m_params.CompareValue1.HasValue ?
                m_params.CompareValue1.Value : DEFAULT_COMPARE_VALUE_1;

            UInt16 Compare2Value16 = m_params.CompareValue2.HasValue ?
                m_params.CompareValue2.Value : DEFAULT_COMPARE_VALUE_1;

            float dbcounts = (float)(DeadTimeValue32 + 1) * bitwidth;
            PointF[] pts = new PointF[18]; //Maximum is 16 values.
            PointF[] ptsDBph1 = new PointF[12];
            PointF[] ptsDBph2 = new PointF[12];

            for (int i = 0; i < numwaveforms; i++)
            {
                float HighY = PB_EXTENTS_BORDER + (2 * PB_POLYGON_WIDTH) + (wfheight * i) + (wfheight / 8);
                float LowY = PB_EXTENTS_BORDER + (2 * PB_POLYGON_WIDTH) + (wfheight * (i + 1));
                float CenterY = HighY + ((LowY - HighY) / 2);
                switch (wfnames[i])
                {
                    #region PWM1
                    case PWM1:
                        // Find the parameters for PWM1
                        Edge1 = startleft + (bitwidth * (float)(PeriodValue32 - CompareValue32));
                        Edge1_2 = startright + (bitwidth * (float)(PeriodValue32 - CompareValue32));

                        // "Less" OR "Less than or equal" compare type 
                        if (m_params.CompareType1.Value == CyECompareType.B_PWM__Less_Than ||
                            m_params.CompareType1.Value == CyECompareType.B_PWM__Less_Than_Or_Equal)
                        {
                            StartHigh = false;

                            if (m_params.CompareType1.Value != CyECompareType.B_PWM__Less_Than_Or_Equal)
                            {
                                Edge1 += bitwidth;
                                Edge1_2 += bitwidth;
                            }

                            if ((CompareValue32 > PeriodValue32) ||
                                ((CompareValue32 >= PeriodValue32) &&
                                (m_params.CompareType1.Value == CyECompareType.B_PWM__Less_Than_Or_Equal)))
                            {
                                PointF point = new PointF(startleft, StartHigh ? LowY : HighY);
                                InitializePointArray(pts, 0, 16, point);
                                pts[17] = new PointF(endright, StartHigh ? LowY : HighY);
                            }
                            else
                            {
                                //Draw the first version of the waveform from StartLeft to StartRight
                                pts[0] = new PointF(startleft, StartHigh ? HighY : LowY);
                                pts[1] = new PointF(Edge1, StartHigh ? HighY : LowY);
                                if ((CompareValue32 == 0) &&
                                    (m_params.CompareType1.Value != CyECompareType.B_PWM__Less_Than_Or_Equal))
                                {
                                    pts[2] = new PointF(Edge1, StartHigh ? HighY : LowY);
                                    pts[3] = new PointF(Edge1, StartHigh ? HighY : LowY);
                                    //setting the last point of waveform
                                    pts[6] = new PointF(Edge1_2, StartHigh ? HighY : LowY);
                                    pts[7] = new PointF(endright, StartHigh ? HighY : LowY);
                                }
                                else
                                {
                                    pts[2] = new PointF(Edge1, StartHigh ? LowY : HighY);
                                    pts[3] = new PointF(startright, StartHigh ? LowY : HighY);
                                    pts[6] = new PointF(Edge1_2, StartHigh ? LowY : HighY);
                                    pts[7] = new PointF(endright, StartHigh ? LowY : HighY);
                                }
                                pts[4] = new PointF(startright, StartHigh ? HighY : LowY);
                                pts[5] = new PointF(Edge1_2, StartHigh ? HighY : LowY);
                                InitializePointArray(pts, 8, 17, pts[7]);
                            }
                        }
                        // "Greater" OR "Greater than or equal" compare type 
                        else if (m_params.CompareType1.Value == CyECompareType.B_PWM__Greater_Than ||
                                 m_params.CompareType1.Value == CyECompareType.B_PWM__Greater_Than_Or_Equal_To ||
                                 m_params.CompareType1.Value == CyECompareType.B_PWM__Firmware)
                        {
                            StartHigh = true;
                            if ((m_params.CompareType1.Value == CyECompareType.B_PWM__Greater_Than_Or_Equal_To) ||
                                (m_params.CompareType1.Value == CyECompareType.B_PWM__Firmware))
                            {
                                Edge1 += bitwidth;
                                Edge1_2 += bitwidth;
                            }
                            if (((CompareValue32 >= PeriodValue32) &&
                                m_params.CompareType1.Value == CyECompareType.B_PWM__Greater_Than) ||
                              ((CompareValue32 > PeriodValue32) &&
                              ((m_params.CompareType1.Value == CyECompareType.B_PWM__Greater_Than_Or_Equal_To) ||
                              (m_params.CompareType1.Value == CyECompareType.B_PWM__Firmware))))
                            {
                                PointF point = new PointF(startleft, StartHigh ? LowY : HighY);
                                InitializePointArray(pts, 0, 16, point);
                                pts[17] = new PointF(endright, StartHigh ? LowY : HighY);
                            }
                            else
                            {
                                //Draw the first version of the waveform from StartLeft to StartRight
                                pts[0] = new PointF(startleft, StartHigh ? HighY : LowY);
                                pts[1] = new PointF(Edge1, StartHigh ? HighY : LowY);
                                if ((CompareValue32 == 0) &&
                                    ((m_params.CompareType1.Value ==
                                                             CyECompareType.B_PWM__Greater_Than_Or_Equal_To) ||
                                    (m_params.CompareType1.Value == CyECompareType.B_PWM__Firmware)))
                                {
                                    pts[2] = new PointF(Edge1, StartHigh ? HighY : LowY);
                                    pts[3] = new PointF(startright, StartHigh ? HighY : LowY);
                                    pts[6] = new PointF(Edge1_2, StartHigh ? HighY : LowY);
                                    pts[7] = new PointF(endright, StartHigh ? HighY : LowY);
                                }
                                else
                                {
                                    pts[2] = new PointF(Edge1, StartHigh ? LowY : HighY);
                                    pts[3] = new PointF(startright, StartHigh ? LowY : HighY);
                                    pts[6] = new PointF(Edge1_2, StartHigh ? LowY : HighY);
                                    pts[7] = new PointF(endright, StartHigh ? LowY : HighY);
                                }
                                pts[4] = new PointF(startright, StartHigh ? HighY : LowY);
                                pts[5] = new PointF(Edge1_2, StartHigh ? HighY : LowY);
                                InitializePointArray(pts, 8, 17, pts[7]);
                            }
                        }
                        // "Equal" compare type; cmp value > period value 
                        else if ((CompareValue32 > PeriodValue32)
                            && (m_params.CompareType1.Value == CyECompareType.B_PWM__Equal))
                        {

                            StartHigh = true;
                            Edge1 += bitwidth;
                            Edge1_2 += bitwidth;

                            PointF point = new PointF(startleft, StartHigh ? LowY : HighY);
                            InitializePointArray(pts, 0, 16, point);
                            pts[17] = new PointF(endright, StartHigh ? LowY : HighY);
                        }
                        else
                        {
                            // Here we consider "Firmware control" compare type 
                            StartHigh = false;
                            Edge2 = Edge1 + bitwidth;
                            Edge2_2 = Edge1_2 + bitwidth;
                            // Draw the first version of the waveform from StartLeft to StartRight
                            pts[0] = new PointF(startleft, LowY);
                            pts[1] = new PointF(Edge1, LowY);
                            pts[2] = new PointF(Edge1, HighY);
                            pts[3] = new PointF(Edge2, HighY);
                            pts[4] = new PointF(Edge2, LowY);
                            pts[5] = new PointF(Edge1_2, LowY);
                            pts[6] = new PointF(Edge1_2, HighY);
                            pts[7] = new PointF(Edge2_2, HighY);
                            pts[8] = new PointF(Edge2_2, LowY);
                            pts[9] = new PointF(endright, LowY);
                            InitializePointArray(pts, 10, 17, pts[9]);
                        }

                        if (StartHigh)
                        {
                            ptsDBph1[0] = new PointF(startleft, 0f);
                            ptsDBph1[1] = new PointF(startleft + dbcounts, 0f);
                            ptsDBph1[2] = new PointF(startleft + dbcounts, 1f);
                            ptsDBph1[3] = new PointF(Edge1, 1f);
                            ptsDBph1[4] = new PointF(Edge1, 0f);
                            ptsDBph1[5] = new PointF(startright, 0f);
                            ptsDBph1[6] = new PointF(startright, 0f);
                            ptsDBph1[7] = new PointF(startright + dbcounts, 0f);
                            ptsDBph1[8] = new PointF(startright + dbcounts, 1f);
                            ptsDBph1[9] = new PointF(Edge1_2, 1f);
                            ptsDBph1[10] = new PointF(Edge1_2, 0f);
                            ptsDBph1[11] = new PointF(endright, 0f);
                            ptsDBph2[0] = new PointF(startleft, 0f);
                            ptsDBph2[1] = new PointF(Edge1 + dbcounts, 0f);
                            ptsDBph2[2] = new PointF(Edge1 + dbcounts, 1f);
                            ptsDBph2[3] = new PointF(startright, 1f);
                            ptsDBph2[4] = new PointF(startright, 0f);
                            ptsDBph2[5] = new PointF(Edge1_2 + dbcounts, 0f);
                            ptsDBph2[6] = new PointF(Edge1_2 + dbcounts, 1f);
                            ptsDBph2[7] = new PointF(endright, 1f);
                            InitializePointArray(ptsDBph2, 8, 11, ptsDBph2[7]);
                        }
                        else
                        {
                            ptsDBph1[0] = new PointF(startleft, 0f);
                            ptsDBph1[1] = new PointF(Edge1 + dbcounts, 0f);
                            ptsDBph1[2] = new PointF(Edge1 + dbcounts, 1f);
                            ptsDBph1[3] = new PointF(startright, 1f);
                            ptsDBph1[4] = new PointF(startright, 0f);
                            ptsDBph1[5] = new PointF(Edge1_2 + dbcounts, 0f);
                            ptsDBph1[6] = new PointF(Edge1_2 + dbcounts, 1f);
                            ptsDBph1[7] = new PointF(endright, 1f);
                            InitializePointArray(ptsDBph1, 8, 11, ptsDBph1[7]);
                            ptsDBph2[0] = new PointF(startleft, 0f);
                            ptsDBph2[1] = new PointF(startleft + dbcounts, 0f);
                            ptsDBph2[2] = new PointF(startleft + dbcounts, 1f);
                            ptsDBph2[3] = new PointF(Edge1, 1f);
                            ptsDBph2[4] = new PointF(Edge1, 0f);
                            ptsDBph2[5] = new PointF(startright, 0f);
                            ptsDBph2[6] = new PointF(startright, 0f);
                            ptsDBph2[7] = new PointF(startright + dbcounts, 0f);
                            ptsDBph2[8] = new PointF(startright + dbcounts, 1f);
                            ptsDBph2[9] = new PointF(Edge1_2, 1f);
                            ptsDBph2[10] = new PointF(Edge1_2, 0f);
                            ptsDBph2[11] = new PointF(endright, 0f);
                        }
                        break;
                    #endregion
                    #region PWM2
                    case PWM2:
                        //Find the parameters for PWM2
                        Edge1 = startleft + (bitwidth * (float)(PeriodValue32 - Compare2Value32));
                        Edge1_2 = startright + (bitwidth * (float)(PeriodValue32 - Compare2Value32));
                        if (m_params.CompareType2.Value == CyECompareType.B_PWM__Less_Than ||
                            m_params.CompareType2.Value == CyECompareType.B_PWM__Less_Than_Or_Equal)
                        {
                            StartHigh = false;
                            if (m_params.CompareType2.Value != CyECompareType.B_PWM__Less_Than_Or_Equal)
                            {
                                Edge1 += bitwidth;
                                Edge1_2 += bitwidth;
                            }

                            if ((Compare2Value32 > PeriodValue32) ||
                               ((Compare2Value32 >= PeriodValue32) &&
                                m_params.CompareType2.Value == CyECompareType.B_PWM__Less_Than_Or_Equal))
                            {
                                pts[0] = new PointF(startleft, StartHigh ? LowY : HighY);
                                InitializePointArray(pts, 1, 16, pts[0]);
                                pts[17] = new PointF(endright, StartHigh ? LowY : HighY);
                            }
                            else
                            {
                                pts[0] = new PointF(startleft, StartHigh ? HighY : LowY);
                                pts[1] = new PointF(Edge1, StartHigh ? HighY : LowY);
                                if ((Compare2Value32 == 0) &&
                                    (m_params.CompareType2.Value != CyECompareType.B_PWM__Less_Than_Or_Equal))
                                {
                                    pts[2] = new PointF(Edge1, StartHigh ? HighY : LowY);
                                    pts[3] = new PointF(Edge1, StartHigh ? HighY : LowY);
                                    //setting the last point of waveform
                                    pts[6] = new PointF(Edge1_2, StartHigh ? HighY : LowY);
                                    pts[7] = new PointF(endright, StartHigh ? HighY : LowY);
                                }
                                else
                                {
                                    pts[2] = new PointF(Edge1, StartHigh ? LowY : HighY);
                                    pts[3] = new PointF(startright, StartHigh ? LowY : HighY);
                                    pts[6] = new PointF(Edge1_2, StartHigh ? LowY : HighY);
                                    pts[7] = new PointF(endright, StartHigh ? LowY : HighY);
                                }
                                pts[4] = new PointF(startright, StartHigh ? HighY : LowY);
                                pts[5] = new PointF(Edge1_2, StartHigh ? HighY : LowY);
                                InitializePointArray(pts, 8, 17, pts[7]);
                            }
                        }
                        else if (m_params.CompareType2.Value == CyECompareType.B_PWM__Greater_Than ||
                            m_params.CompareType2.Value == CyECompareType.B_PWM__Greater_Than_Or_Equal_To ||
                            m_params.CompareType2.Value == CyECompareType.B_PWM__Firmware)
                        {
                            StartHigh = true;
                            if ((m_params.CompareType2.Value == CyECompareType.B_PWM__Greater_Than_Or_Equal_To) ||
                                (m_params.CompareType2.Value == CyECompareType.B_PWM__Firmware))
                            {
                                Edge1 += bitwidth;
                                Edge1_2 += bitwidth;
                            }

                            if (((Compare2Value32 >= PeriodValue32) && m_params.CompareType2.Value ==
                                                                    CyECompareType.B_PWM__Greater_Than) ||
                              ((Compare2Value32 > PeriodValue32) && ((m_params.CompareType2.Value ==
                                                                    CyECompareType.B_PWM__Greater_Than_Or_Equal_To) ||
                              (m_params.CompareType2.Value == CyECompareType.B_PWM__Firmware))))
                            {
                                pts[0] = new PointF(startleft, StartHigh ? LowY : HighY);
                                InitializePointArray(pts, 1, 16, pts[0]);
                                pts[17] = new PointF(endright, StartHigh ? LowY : HighY);
                            }
                            else
                            {
                                pts[0] = new PointF(startleft, StartHigh ? HighY : LowY);
                                pts[1] = new PointF(Edge1, StartHigh ? HighY : LowY);
                                if ((Compare2Value32 == 0) &&
                                    ((m_params.CompareType2.Value ==
                                                           CyECompareType.B_PWM__Greater_Than_Or_Equal_To) ||
                                    (m_params.CompareType2.Value == CyECompareType.B_PWM__Firmware)))
                                {
                                    pts[2] = new PointF(Edge1, StartHigh ? HighY : LowY);
                                    pts[3] = new PointF(startright, StartHigh ? HighY : LowY);
                                    pts[6] = new PointF(Edge1_2, StartHigh ? HighY : LowY);
                                    pts[7] = new PointF(endright, StartHigh ? HighY : LowY);
                                }
                                else
                                {
                                    pts[2] = new PointF(Edge1, StartHigh ? LowY : HighY);
                                    pts[3] = new PointF(startright, StartHigh ? LowY : HighY);
                                    //setting the last point of waveform
                                    pts[6] = new PointF(Edge1_2, StartHigh ? LowY : HighY);
                                    pts[7] = new PointF(endright, StartHigh ? LowY : HighY);
                                }
                                pts[4] = new PointF(startright, StartHigh ? HighY : LowY);
                                pts[5] = new PointF(Edge1_2, StartHigh ? HighY : LowY);
                                InitializePointArray(pts, 8, 17, pts[7]);
                            }
                        }
                        else if ((Compare2Value32 > PeriodValue32)
                            && (m_params.CompareType2.Value == CyECompareType.B_PWM__Equal))
                        {
                            StartHigh = true;
                            Edge1 += bitwidth;
                            Edge1_2 += bitwidth;
                            pts[0] = new PointF(startleft, StartHigh ? LowY : HighY);
                            InitializePointArray(pts, 1, 16, pts[0]);
                            pts[17] = new PointF(endright, StartHigh ? LowY : HighY);
                        }
                        else
                        {
                            StartHigh = false;
                            Edge2 = Edge1 + bitwidth;
                            Edge2_2 = Edge1_2 + bitwidth;
                            //Draw the first version of the waveform from StartLeft to StartRight
                            pts[0] = new PointF(startleft, LowY);
                            pts[1] = new PointF(Edge1, LowY);
                            pts[2] = new PointF(Edge1, HighY);
                            pts[3] = new PointF(Edge2, HighY);
                            pts[4] = new PointF(Edge2, LowY);
                            pts[5] = new PointF(Edge1_2, LowY);
                            pts[6] = new PointF(Edge1_2, HighY);
                            pts[7] = new PointF(Edge2_2, HighY);
                            pts[8] = new PointF(Edge2_2, LowY);
                            pts[9] = new PointF(endright, LowY);
                            InitializePointArray(pts, 10, 17, pts[9]);
                        }
                        break;
                    #endregion
                    #region PWM
                    case PWM:
                        //Find the parameters for PWM
                        #region PWM-ONE
                        if (m_params.PwmMode.Value == CyEPwmMode.B_PWM__One_Output)
                        {
                            Edge1 = startleft + (bitwidth * (float)(PeriodValue32 - CompareValue32));
                            Edge1_2 = startright + (bitwidth * (float)(PeriodValue32 - CompareValue32));
                            if (m_params.CompareType1.Value == CyECompareType.B_PWM__Less_Than ||
                                m_params.CompareType1.Value == CyECompareType.B_PWM__Less_Than_Or_Equal)
                            {
                                StartHigh = false;
                                if (m_params.CompareType1.Value != CyECompareType.B_PWM__Less_Than_Or_Equal)
                                {
                                    Edge1 += bitwidth;
                                    Edge1_2 += bitwidth;
                                }

                                if ((CompareValue32 > PeriodValue32) ||
                                   ((CompareValue32 >= PeriodValue32) &&
                                    m_params.CompareType1.Value == CyECompareType.B_PWM__Less_Than_Or_Equal))
                                {
                                    pts[0] = new PointF(startleft, StartHigh ? LowY : HighY);
                                    InitializePointArray(pts, 1, 16, pts[0]);
                                    pts[17] = new PointF(endright, StartHigh ? LowY : HighY);
                                }
                                else
                                {
                                    pts[0] = new PointF(startleft, StartHigh ? HighY : LowY);
                                    pts[1] = new PointF(Edge1, StartHigh ? HighY : LowY);
                                    if ((CompareValue32 == 0) &&
                                        (m_params.CompareType1.Value != CyECompareType.B_PWM__Less_Than_Or_Equal))
                                    {
                                        pts[2] = new PointF(Edge1, StartHigh ? HighY : LowY);
                                        pts[3] = new PointF(Edge1, StartHigh ? HighY : LowY);
                                        pts[6] = new PointF(Edge1_2, StartHigh ? HighY : LowY);
                                        pts[7] = new PointF(endright, StartHigh ? HighY : LowY);
                                    }
                                    else
                                    {
                                        pts[2] = new PointF(Edge1, StartHigh ? LowY : HighY);
                                        pts[3] = new PointF(startright, StartHigh ? LowY : HighY);
                                        pts[6] = new PointF(Edge1_2, StartHigh ? LowY : HighY);
                                        pts[7] = new PointF(endright, StartHigh ? LowY : HighY);
                                    }
                                    pts[4] = new PointF(startright, StartHigh ? HighY : LowY);
                                    pts[5] = new PointF(Edge1_2, StartHigh ? HighY : LowY);
                                    InitializePointArray(pts, 8, 17, pts[7]);
                                }
                            }
                            else if (m_params.CompareType1.Value == CyECompareType.B_PWM__Greater_Than ||
                                m_params.CompareType1.Value == CyECompareType.B_PWM__Greater_Than_Or_Equal_To ||
                                m_params.CompareType1.Value == CyECompareType.B_PWM__Firmware)
                            {
                                StartHigh = true;
                                if ((m_params.CompareType1.Value == CyECompareType.B_PWM__Greater_Than_Or_Equal_To) ||
                                    (m_params.CompareType1.Value == CyECompareType.B_PWM__Firmware))
                                {
                                    Edge1 += bitwidth;
                                    Edge1_2 += bitwidth;
                                }

                                if (((CompareValue32 >= PeriodValue32) &&
                                    m_params.CompareType1.Value == CyECompareType.B_PWM__Greater_Than) ||
                                    ((CompareValue32 > PeriodValue32) &&
                                    ((m_params.CompareType1.Value ==
                                                        CyECompareType.B_PWM__Greater_Than_Or_Equal_To) ||
                                    (m_params.CompareType1.Value == CyECompareType.B_PWM__Firmware))))
                                {
                                    pts[0] = new PointF(startleft, StartHigh ? LowY : HighY);
                                    InitializePointArray(pts, 1, 16, pts[0]);
                                    pts[17] = new PointF(endright, StartHigh ? LowY : HighY);
                                }
                                else
                                {
                                    pts[0] = new PointF(startleft, StartHigh ? HighY : LowY);
                                    pts[1] = new PointF(Edge1, StartHigh ? HighY : LowY);
                                    if ((CompareValue32 == 0) &&
                                        ((m_params.CompareType1.Value ==
                                                            CyECompareType.B_PWM__Greater_Than_Or_Equal_To) ||
                                        (m_params.CompareType1.Value == CyECompareType.B_PWM__Firmware)))
                                    {
                                        pts[2] = new PointF(Edge1, StartHigh ? HighY : LowY);
                                        pts[3] = new PointF(startright, StartHigh ? HighY : LowY);
                                        pts[6] = new PointF(Edge1_2, StartHigh ? HighY : LowY);
                                        pts[7] = new PointF(endright, StartHigh ? HighY : LowY);
                                    }
                                    else
                                    {
                                        pts[2] = new PointF(Edge1, StartHigh ? LowY : HighY);
                                        pts[3] = new PointF(startright, StartHigh ? LowY : HighY);
                                        pts[6] = new PointF(Edge1_2, StartHigh ? LowY : HighY);
                                        pts[7] = new PointF(endright, StartHigh ? LowY : HighY);
                                    }
                                    pts[4] = new PointF(startright, StartHigh ? HighY : LowY);
                                    pts[5] = new PointF(Edge1_2, StartHigh ? HighY : LowY);
                                    InitializePointArray(pts, 8, 17, pts[7]);
                                }
                            }
                            else if ((CompareValue32 > PeriodValue32)
                                && (m_params.CompareType1.Value == CyECompareType.B_PWM__Equal))
                            {
                                StartHigh = true;
                                Edge1 += bitwidth;
                                Edge1_2 += bitwidth;
                                pts[0] = new PointF(startleft, StartHigh ? LowY : HighY);
                                InitializePointArray(pts, 1, 16, pts[0]);
                                pts[17] = new PointF(endright, StartHigh ? LowY : HighY);
                            }
                            else
                            {
                                StartHigh = false;
                                Edge2 = Edge1 + bitwidth;
                                Edge2_2 = Edge1_2 + bitwidth;
                                //Draw the first version of the waveform from StartLeft to StartRight
                                pts[0] = new PointF(startleft, LowY);
                                pts[1] = new PointF(Edge1, LowY);
                                pts[2] = new PointF(Edge1, HighY);
                                pts[3] = new PointF(Edge2, HighY);
                                pts[4] = new PointF(Edge2, LowY);
                                pts[5] = new PointF(Edge1_2, LowY);
                                pts[6] = new PointF(Edge1_2, HighY);
                                pts[7] = new PointF(Edge2_2, HighY);
                                pts[8] = new PointF(Edge2_2, LowY);
                                pts[9] = new PointF(endright, LowY);
                                InitializePointArray(pts, 10, 17, pts[9]);
                            }
                            if (StartHigh)
                            {
                                ptsDBph1[0] = new PointF(startleft, 0f);
                                ptsDBph1[1] = new PointF(startleft + dbcounts, 0f);
                                ptsDBph1[2] = new PointF(startleft + dbcounts, 1f);
                                ptsDBph1[3] = new PointF(Edge1, 1f);
                                ptsDBph1[4] = new PointF(Edge1, 0f);
                                ptsDBph1[5] = new PointF(startright, 0f);
                                ptsDBph1[6] = new PointF(startright, 0f);
                                ptsDBph1[7] = new PointF(startright + dbcounts, 0f);
                                ptsDBph1[8] = new PointF(startright + dbcounts, 1f);
                                ptsDBph1[9] = new PointF(Edge1_2, 1f);
                                ptsDBph1[10] = new PointF(Edge1_2, 0f);
                                ptsDBph1[11] = new PointF(endright, 0f);
                                ptsDBph2[0] = new PointF(startleft, 0f);
                                ptsDBph2[1] = new PointF(Edge1 + dbcounts, 0f);
                                ptsDBph2[2] = new PointF(Edge1 + dbcounts, 1f);
                                ptsDBph2[3] = new PointF(startright, 1f);
                                ptsDBph2[4] = new PointF(startright, 0f);
                                ptsDBph2[5] = new PointF(Edge1_2 + dbcounts, 0f);
                                ptsDBph2[6] = new PointF(Edge1_2 + dbcounts, 1f);
                                ptsDBph2[7] = new PointF(endright, 1f);
                                ptsDBph2[8] = ptsDBph2[7];
                                ptsDBph2[9] = ptsDBph2[7];
                                ptsDBph2[10] = ptsDBph2[7];
                                ptsDBph2[11] = ptsDBph2[7];
                            }
                            else
                            {
                                ptsDBph1[0] = new PointF(startleft, 0f);
                                ptsDBph1[1] = new PointF(Edge1 + dbcounts, 0f);
                                ptsDBph1[2] = new PointF(Edge1 + dbcounts, 1f);
                                ptsDBph1[3] = new PointF(startright, 1f);
                                ptsDBph1[4] = new PointF(startright, 0f);
                                ptsDBph1[5] = new PointF(Edge1_2 + dbcounts, 0f);
                                ptsDBph1[6] = new PointF(Edge1_2 + dbcounts, 1f);
                                ptsDBph1[7] = new PointF(endright, 1f);
                                ptsDBph1[8] = ptsDBph1[7];
                                ptsDBph1[9] = ptsDBph1[7];
                                ptsDBph1[10] = ptsDBph1[7];
                                ptsDBph1[11] = ptsDBph1[7];
                                ptsDBph2[0] = new PointF(startleft, 0f);
                                ptsDBph2[1] = new PointF(startleft + dbcounts, 0f);
                                ptsDBph2[2] = new PointF(startleft + dbcounts, 1f);
                                ptsDBph2[3] = new PointF(Edge1, 1f);
                                ptsDBph2[4] = new PointF(Edge1, 0f);
                                ptsDBph2[5] = new PointF(startright, 0f);
                                ptsDBph2[6] = new PointF(startright, 0f);
                                ptsDBph2[7] = new PointF(startright + dbcounts, 0f);
                                ptsDBph2[8] = new PointF(startright + dbcounts, 1f);
                                ptsDBph2[9] = new PointF(Edge1_2, 1f);
                                ptsDBph2[10] = new PointF(Edge1_2, 0f);
                                ptsDBph2[11] = new PointF(endright, 0f);
                            }
                        }
                        #endregion
                        #region PWM-DUAL
                        if (m_params.PwmMode.Value == CyEPwmMode.B_PWM__Dual_Edge)
                        {
                            string cmptype1 = "0";
                            string cmptype2 = "0";
                            Edge1 = startleft + (bitwidth * (float)(PeriodValue32 - CompareValue32));
                            Edge1_2 = startright + (bitwidth * (float)(PeriodValue32 - CompareValue32));
                            Edge2 = startleft + (bitwidth * (float)(PeriodValue32 - Compare2Value32));
                            Edge2_2 = startright + (bitwidth * (float)(PeriodValue32 - Compare2Value32));

                            if (m_params.CompareType1.Value == CyECompareType.B_PWM__Less_Than ||
                                m_params.CompareType1.Value == CyECompareType.B_PWM__Less_Than_Or_Equal)
                            {
                                cmptype1 = "0";
                                if (m_params.CompareType1.Value != CyECompareType.B_PWM__Less_Than_Or_Equal)
                                {
                                    Edge1 += bitwidth;
                                    Edge1_2 += bitwidth;
                                }
                            }

                            else if (m_params.CompareType1.Value == CyECompareType.B_PWM__Greater_Than ||
                                m_params.CompareType1.Value == CyECompareType.B_PWM__Greater_Than_Or_Equal_To ||
                                m_params.CompareType1.Value == CyECompareType.B_PWM__Firmware)
                            {
                                cmptype1 = "1";
                                if ((m_params.CompareType1.Value ==
                                                        CyECompareType.B_PWM__Greater_Than_Or_Equal_To) ||
                                    (m_params.CompareType1.Value == CyECompareType.B_PWM__Firmware))
                                {
                                    Edge1 += bitwidth;
                                    Edge1_2 += bitwidth;
                                }
                            }
                            else
                            {
                                cmptype1 = "X";
                                StartHigh = false;
                                Edge3 = Edge1 + bitwidth;
                                Edge3_2 = Edge1_2 + bitwidth;
                            }

                            //Get Compare Type Information for Compare Type 2
                            if (m_params.CompareType2.Value == CyECompareType.B_PWM__Less_Than ||
                                m_params.CompareType2.Value == CyECompareType.B_PWM__Less_Than_Or_Equal)
                            {
                                cmptype2 = "0";
                                if (m_params.CompareType2.Value != CyECompareType.B_PWM__Less_Than_Or_Equal)
                                {
                                    Edge2 += bitwidth;
                                    Edge2_2 += bitwidth;
                                }
                            }
                            else if (m_params.CompareType2.Value == CyECompareType.B_PWM__Greater_Than ||
                                m_params.CompareType2.Value == CyECompareType.B_PWM__Greater_Than_Or_Equal_To ||
                               m_params.CompareType2.Value == CyECompareType.B_PWM__Firmware)
                            {
                                cmptype2 = "1";
                                if ((m_params.CompareType2.Value ==
                                                        CyECompareType.B_PWM__Greater_Than_Or_Equal_To) ||
                                    (m_params.CompareType2.Value == CyECompareType.B_PWM__Firmware))
                                {
                                    Edge2 += bitwidth;
                                    Edge2_2 += bitwidth;
                                }
                            }
                            else
                            {
                                cmptype2 = "X";
                                Edge4 = Edge2 + bitwidth;
                                Edge4_2 = Edge2_2 + bitwidth;
                            }

                            switch (cmptype1 + cmptype2)
                            {
                                case "00": // Compare1 = Less Than, Compare2 = Less Than
                                    if ((CompareValue32 > PeriodValue32) &&
                                        (Compare2Value32 > PeriodValue32))
                                    {
                                        StartHigh = true;
                                        Edge1 += bitwidth;
                                        Edge1_2 += bitwidth;
                                        pts[0] = new PointF(startleft, StartHigh ? HighY : LowY);
                                        InitializePointArray(pts, 1, 16, pts[0]);
                                        pts[17] = new PointF(endright, StartHigh ? HighY : LowY);
                                    }
                                    else
                                    {
                                        StartHigh = false;
                                        pts[0] = new PointF(startleft, LowY);
                                        pts[1] = new PointF(Math.Max(Edge1, Edge2), LowY);
                                        pts[2] = new PointF(Math.Max(Edge1, Edge2), HighY);
                                        pts[3] = new PointF(startright, HighY);
                                        pts[4] = new PointF(startright, LowY);
                                        pts[5] = new PointF(Math.Max(Edge1_2, Edge2_2), LowY);
                                        pts[6] = new PointF(Math.Max(Edge1_2, Edge2_2), HighY);
                                        pts[7] = new PointF(endright, HighY);
                                        InitializePointArray(pts, 8, 17, pts[7]);
                                    }

                                    if ((Math.Max(Edge1, Edge2) + dbcounts) < startright)
                                    {
                                        ptsDBph1[0] = new PointF(startleft, 0f);
                                        ptsDBph1[1] = new PointF(Math.Max(Edge1, Edge2) + dbcounts, 0f);
                                        ptsDBph1[2] = new PointF(Math.Max(Edge1, Edge2) + dbcounts, 1f);
                                        ptsDBph1[3] = new PointF(startright, 1f);
                                        ptsDBph1[4] = new PointF(startright, 0f);
                                        ptsDBph1[5] = new PointF(Math.Max(Edge1_2, Edge2_2) + dbcounts, 0f);
                                        ptsDBph1[6] = new PointF(Math.Max(Edge1_2, Edge2_2) + dbcounts, 1f);
                                        ptsDBph1[7] = new PointF(endright, 1f);
                                        ptsDBph1[8] = ptsDBph1[7];
                                        ptsDBph1[9] = ptsDBph1[7];
                                        ptsDBph1[10] = ptsDBph1[7];
                                        ptsDBph1[11] = ptsDBph1[7];
                                    }
                                    else
                                    {
                                        ptsDBph1[0] = new PointF(startleft, 0f);
                                        ptsDBph1[1] = new PointF(endright, 0f);
                                        InitializePointArray(ptsDBph1, 2, 11, ptsDBph1[1]);
                                    }

                                    if ((startleft + dbcounts) < Math.Max(Edge1, Edge2))
                                    {
                                        ptsDBph2[0] = new PointF(startleft, 0f);
                                        ptsDBph2[1] = new PointF(startleft + dbcounts, 0f);
                                        ptsDBph2[2] = new PointF(startleft + dbcounts, 1f);
                                        ptsDBph2[3] = new PointF(Math.Max(Edge1, Edge2), 1f);
                                        ptsDBph2[4] = new PointF(Math.Max(Edge1, Edge2), 0f);
                                        ptsDBph2[5] = new PointF(startright, 0f);
                                        ptsDBph2[6] = new PointF(startright, 0f);
                                        ptsDBph2[7] = new PointF(startright + dbcounts, 0f);
                                        ptsDBph2[8] = new PointF(startright + dbcounts, 1f);
                                        ptsDBph2[9] = new PointF(Math.Max(Edge1_2, Edge2_2), 1f);
                                        ptsDBph2[10] = new PointF(Math.Max(Edge1_2, Edge2_2), 0f);
                                        ptsDBph2[11] = new PointF(endright, 0f);
                                    }
                                    else
                                    {
                                        ptsDBph2[0] = new PointF(startleft, 0f);
                                        ptsDBph2[1] = new PointF(endright, 0f);
                                        InitializePointArray(ptsDBph2, 2, 11, ptsDBph2[1]);
                                    }
                                    break;
                                case "01":
                                case "10"://Low to High To Low

                                    if (CompareValue32 > PeriodValue32)
                                    {
                                        StartHigh = true;
                                        Edge1 += bitwidth;
                                        Edge1_2 += bitwidth;
                                        pts[0] = new PointF(startleft, StartHigh ? LowY : HighY);
                                        InitializePointArray(pts, 1, 16, pts[0]);
                                        pts[17] = new PointF(endright, StartHigh ? LowY : HighY);
                                    }
                                    else
                                    {
                                        StartHigh = false;
                                        if ((((cmptype1 + cmptype2) == "01") && (Edge1 < Edge2)) ||
                                            (((cmptype1 + cmptype2) == "10") && (Edge2 < Edge1)))
                                        {
                                            pts[0] = new PointF(startleft, LowY);
                                            pts[1] = new PointF(Math.Min(Edge1, Edge2), LowY);
                                            pts[2] = new PointF(Math.Min(Edge1, Edge2), HighY);
                                            pts[3] = new PointF(Math.Max(Edge1, Edge2), HighY);
                                            pts[4] = new PointF(Math.Max(Edge1, Edge2), LowY);
                                            pts[5] = new PointF(startright, LowY);
                                            pts[6] = new PointF(startright, LowY);
                                            pts[7] = new PointF(Math.Min(Edge1_2, Edge2_2), LowY);
                                            pts[8] = new PointF(Math.Min(Edge1_2, Edge2_2), HighY);
                                            pts[9] = new PointF(Math.Max(Edge1_2, Edge2_2), HighY);
                                            pts[10] = new PointF(Math.Max(Edge1_2, Edge2_2), LowY);
                                            pts[11] = new PointF(endright, LowY);
                                            InitializePointArray(pts, 12, 17, pts[11]);
                                        }
                                        else
                                        {
                                            pts[0] = new PointF(startleft, LowY);
                                            pts[1] = new PointF(endright, LowY);
                                            InitializePointArray(pts, 2, 17, pts[1]);
                                        }

                                        if ((((cmptype1 + cmptype2) == "01") && (Edge1 < Edge2)) ||
                                            (((cmptype1 + cmptype2) == "10") && (Edge2 < Edge1)))
                                        {
                                            if ((Math.Min(Edge1, Edge2) + dbcounts) < Math.Max(Edge1, Edge2))
                                            {
                                                ptsDBph1[0] = new PointF(startleft, 0f);
                                                ptsDBph1[1] = new PointF(Math.Min(Edge1, Edge2) + dbcounts, 0f);
                                                ptsDBph1[2] = new PointF(Math.Min(Edge1, Edge2) + dbcounts, 1f);
                                                ptsDBph1[3] = new PointF(Math.Max(Edge1, Edge2), 1f);
                                                ptsDBph1[4] = new PointF(Math.Max(Edge1, Edge2), 0f);
                                                ptsDBph1[5] = new PointF(startright, 0f);
                                                ptsDBph1[6] = new PointF(startright, 0f);
                                                ptsDBph1[7] = new PointF(Math.Min(Edge1_2, Edge2_2) + dbcounts, 0f);
                                                ptsDBph1[8] = new PointF(Math.Min(Edge1_2, Edge2_2) + dbcounts, 1f);
                                                ptsDBph1[9] = new PointF(Math.Max(Edge1_2, Edge2_2), 1f);
                                                ptsDBph1[10] = new PointF(Math.Max(Edge1_2, Edge2_2), 0f);
                                                ptsDBph1[11] = new PointF(endright, 0f);
                                            }
                                            else
                                            {
                                                ptsDBph1[0] = new PointF(startleft, 0f);
                                                ptsDBph1[1] = new PointF(endright, 0f);
                                                InitializePointArray(ptsDBph1, 2, 11, ptsDBph1[1]);
                                            }
                                        }
                                        else
                                        {
                                            ptsDBph1[0] = new PointF(startleft, 0f);
                                            ptsDBph1[1] = new PointF(endright, 0f);
                                            InitializePointArray(ptsDBph1, 2, 11, ptsDBph1[1]);
                                        }

                                        if ((((cmptype1 + cmptype2) == "01") && (Edge1 < Edge2)) ||
                                            (((cmptype1 + cmptype2) == "10") && (Edge2 < Edge1)))
                                        {
                                            ptsDBph2[0] = new PointF(startleft, 1f);
                                            ptsDBph2[1] = new PointF(Math.Min(Edge1, Edge2), 1f);
                                            ptsDBph2[2] = new PointF(Math.Min(Edge1, Edge2), 0f);
                                            ptsDBph2[3] = new PointF(Math.Max(Edge1, Edge2) + dbcounts, 0f);
                                            ptsDBph2[4] = new PointF(Math.Max(Edge1, Edge2) + dbcounts, 1f);
                                            ptsDBph2[5] = new PointF(startright, 1f);
                                            ptsDBph2[6] = new PointF(startright, 1f);
                                            ptsDBph2[7] = new PointF(Math.Min(Edge1_2, Edge2_2), 1f);
                                            ptsDBph2[8] = new PointF(Math.Min(Edge1_2, Edge2_2), 0f);
                                            ptsDBph2[9] = new PointF(Math.Max(Edge1_2, Edge2_2) + dbcounts, 0f);
                                            ptsDBph2[10] = new PointF(Math.Max(Edge1_2, Edge2_2) + dbcounts, 1f);
                                            ptsDBph2[11] = new PointF(endright, 1f);
                                        }
                                        else
                                        {
                                            ptsDBph2[0] = new PointF(startleft, 0f);
                                            ptsDBph2[1] = new PointF(endright, 0f);
                                            InitializePointArray(ptsDBph2, 2, 11, ptsDBph2[1]);
                                        }
                                    }
                                    break;
                                case "11": // High to Low
                                    if ((CompareValue32 > PeriodValue32) ||
                                        (Compare2Value32 > PeriodValue32))
                                    {
                                        StartHigh = true;
                                        Edge1 += bitwidth;
                                        Edge1_2 += bitwidth;
                                        pts[0] = new PointF(startleft, StartHigh ? LowY : HighY);
                                        InitializePointArray(pts, 1, 16, pts[0]);
                                        pts[17] = new PointF(endright, StartHigh ? LowY : HighY);
                                    }
                                    else
                                    {
                                        StartHigh = true;
                                        pts[0] = new PointF(startleft, HighY);
                                        pts[1] = new PointF(Math.Min(Edge1, Edge2), HighY);
                                        pts[2] = new PointF(Math.Min(Edge1, Edge2), LowY);
                                        pts[3] = new PointF(startright, LowY);
                                        pts[4] = new PointF(startright, HighY);
                                        pts[5] = new PointF(Math.Min(Edge1_2, Edge2_2), HighY);
                                        pts[6] = new PointF(Math.Min(Edge1_2, Edge2_2), LowY);
                                        pts[7] = new PointF(endright, LowY);
                                        InitializePointArray(pts, 8, 17, pts[7]);

                                        if ((startleft + dbcounts) < Edge1)
                                        {
                                            ptsDBph1[0] = new PointF(startleft, 0f);
                                            ptsDBph1[1] = new PointF(startleft + dbcounts, 0f);
                                            ptsDBph1[2] = new PointF(startleft + dbcounts, 1f);
                                            ptsDBph1[3] = new PointF(Math.Min(Edge1, Edge2), 1f);
                                            ptsDBph1[4] = new PointF(Math.Min(Edge1, Edge2), 0f);
                                            ptsDBph1[5] = new PointF(startright, 0f);
                                            ptsDBph1[6] = new PointF(startright, 0f);
                                            ptsDBph1[7] = new PointF(startright + dbcounts, 0f);
                                            ptsDBph1[8] = new PointF(startright + dbcounts, 1f);
                                            ptsDBph1[9] = new PointF(Math.Min(Edge1_2, Edge2_2), 1f);
                                            ptsDBph1[10] = new PointF(Math.Min(Edge1_2, Edge2_2), 0f);
                                            ptsDBph1[11] = new PointF(endright, 0f);
                                        }
                                        else
                                        {
                                            ptsDBph1[0] = new PointF(startleft, 0F);
                                            ptsDBph1[1] = new PointF(endright, 0F);
                                            InitializePointArray(ptsDBph1, 2, 11, ptsDBph1[1]);
                                        }
                                        ptsDBph2[0] = new PointF(startleft, 0f);
                                        ptsDBph2[1] = new PointF(Math.Min(Edge1, Edge2) + dbcounts, 0f);
                                        ptsDBph2[2] = new PointF(Math.Min(Edge1, Edge2) + dbcounts, 1f);
                                        ptsDBph2[3] = new PointF(startright, 1f);
                                        ptsDBph2[4] = new PointF(startright, 0f);
                                        ptsDBph2[5] = new PointF(Math.Min(Edge1_2, Edge2_2) + dbcounts, 0f);
                                        ptsDBph2[6] = new PointF(Math.Min(Edge1_2, Edge2_2) + dbcounts, 1f);
                                        ptsDBph2[7] = new PointF(endright, 1f);
                                        ptsDBph2[8] = ptsDBph2[7];
                                        ptsDBph2[9] = ptsDBph2[7];
                                        ptsDBph2[10] = ptsDBph2[7];
                                        ptsDBph2[11] = ptsDBph2[7];
                                    }
                                    break;
                                case "XX": //cmp1type = "Equal", cmp2type = "Equal"
                                    if ((CompareValue32 > PeriodValue32) ||
                                        (Compare2Value32 > PeriodValue32))
                                    {
                                        StartHigh = true;
                                        Edge1 += bitwidth;
                                        Edge1_2 += bitwidth;
                                        pts[0] = new PointF(startleft, StartHigh ? LowY : HighY);
                                        InitializePointArray(pts, 1, 16, pts[0]);
                                        pts[17] = new PointF(endright, StartHigh ? LowY : HighY);
                                    }
                                    else
                                    {
                                        if (m_params.CompareValue1 == m_params.CompareValue2)
                                        {
                                            pts[0] = new PointF(startleft, LowY);
                                            pts[1] = new PointF(Edge1, LowY);
                                            pts[2] = new PointF(Edge1, HighY);
                                            pts[3] = new PointF(Edge3, HighY);
                                            pts[4] = new PointF(Edge3, LowY);
                                            pts[5] = new PointF(Edge1_2, LowY);
                                            pts[6] = new PointF(Edge1_2, HighY);
                                            pts[7] = new PointF(Edge3_2, HighY);
                                            pts[8] = new PointF(Edge3_2, LowY);
                                            pts[9] = new PointF(endright, LowY);
                                            InitializePointArray(pts, 10, 17, pts[9]);
                                        }
                                        else
                                        {
                                            pts[0] = new PointF(startleft, LowY);
                                            pts[1] = new PointF(endright, LowY);
                                            InitializePointArray(pts, 2, 17, pts[1]);
                                        }
                                    }
                                    break;
                                case "X0": //cmp1type = "Equal", cmp2type = "Less Than"
                                    if (CompareValue32 > PeriodValue32)
                                    {
                                        StartHigh = true;
                                        Edge1 += bitwidth;
                                        Edge1_2 += bitwidth;
                                        pts[0] = new PointF(startleft, StartHigh ? LowY : HighY);
                                        InitializePointArray(pts, 1, 16, pts[0]);
                                        pts[17] = new PointF(endright, StartHigh ? LowY : HighY);
                                    }
                                    else
                                    {
                                        if ((m_params.CompareType2.Value == CyECompareType.B_PWM__Equal &&
                                            (Compare1Value16 <= Compare2Value16)) ||
                                            (Compare1Value16 <= Compare2Value16))
                                        {
                                            pts[0] = new PointF(startleft, LowY);
                                            pts[1] = new PointF(Edge1, LowY);
                                            pts[2] = new PointF(Edge1, HighY);
                                            pts[3] = new PointF(Edge3, HighY);
                                            pts[4] = new PointF(Edge3, LowY);
                                            pts[5] = new PointF(Edge1_2, LowY);
                                            pts[6] = new PointF(Edge1_2, HighY);
                                            pts[7] = new PointF(Edge3_2, HighY);
                                            pts[8] = new PointF(Edge3_2, LowY);
                                            pts[9] = new PointF(endright, LowY);
                                            InitializePointArray(pts, 10, 17, pts[9]);
                                        }
                                        else
                                        {
                                            pts[0] = new PointF(startleft, LowY);
                                            pts[1] = new PointF(endright, LowY);
                                            InitializePointArray(pts, 2, 17, pts[1]);
                                        }
                                    }
                                    break;
                                case "X1": //cmp1type = "Equal", cmp2type = "Great Than"
                                    if ((CompareValue32 > PeriodValue32) ||
                                        (Compare2Value32 > PeriodValue32))
                                    {
                                        StartHigh = true;
                                        Edge1 += bitwidth;
                                        Edge1_2 += bitwidth;
                                        pts[0] = new PointF(startleft, StartHigh ? LowY : HighY);
                                        InitializePointArray(pts, 1, 16, pts[0]);
                                        pts[17] = new PointF(endright, StartHigh ? LowY : HighY);
                                    }
                                    else
                                    {
                                        if ((m_params.CompareType2.Value == CyECompareType.B_PWM__Equal &&
                                            (Compare1Value16 >= Compare2Value16)) ||
                                            (Compare1Value16 > Compare2Value16))
                                        {
                                            pts[0] = new PointF(startleft, LowY);
                                            pts[1] = new PointF(Edge1, LowY);
                                            pts[2] = new PointF(Edge1, HighY);
                                            pts[3] = new PointF(Edge3, HighY);
                                            pts[4] = new PointF(Edge3, LowY);
                                            pts[5] = new PointF(Edge1_2, LowY);
                                            pts[6] = new PointF(Edge1_2, HighY);
                                            pts[7] = new PointF(Edge3_2, HighY);
                                            pts[8] = new PointF(Edge3_2, LowY);
                                            pts[9] = new PointF(endright, LowY);
                                            InitializePointArray(pts, 10, 17, pts[9]);
                                        }
                                        else
                                        {
                                            pts[0] = new PointF(startleft, LowY);
                                            pts[1] = new PointF(endright, LowY);
                                            InitializePointArray(pts, 2, 17, pts[1]);
                                        }
                                    }
                                    break;
                                case "0X": //cmp1type = "Less Than", cmp2type = "Equal"
                                    if (Compare2Value32 > PeriodValue32)
                                    {
                                        StartHigh = true;
                                        Edge1 += bitwidth;
                                        Edge1_2 += bitwidth;
                                        pts[0] = new PointF(startleft, StartHigh ? LowY : HighY);
                                        InitializePointArray(pts, 1, 16, pts[0]);
                                        pts[17] = new PointF(endright, StartHigh ? LowY : HighY);
                                    }
                                    else
                                    {
                                        if ((m_params.CompareType1.Value == CyECompareType.B_PWM__Equal &&
                                            (Compare1Value16 >= Compare2Value16)) ||
                                            (Compare1Value16 > Compare2Value16))
                                        {
                                            pts[0] = new PointF(startleft, LowY);
                                            pts[1] = new PointF(Edge2, LowY);
                                            pts[2] = new PointF(Edge2, HighY);
                                            pts[3] = new PointF(Edge4, HighY);
                                            pts[4] = new PointF(Edge4, LowY);
                                            pts[5] = new PointF(Edge2_2, LowY);
                                            pts[6] = new PointF(Edge2_2, HighY);
                                            pts[7] = new PointF(Edge4_2, HighY);
                                            pts[8] = new PointF(Edge4_2, LowY);
                                            pts[9] = new PointF(endright, LowY);
                                            InitializePointArray(pts, 10, 17, pts[9]);
                                        }
                                        else
                                        {
                                            pts[0] = new PointF(startleft, LowY);
                                            pts[1] = new PointF(endright, LowY);
                                            InitializePointArray(pts, 2, 17, pts[1]);
                                        }
                                    }
                                    break;
                                case "1X": //cmp1type = "Great Than", cmp2type = "Equal"
                                    if (Compare2Value32 > PeriodValue32)
                                    {
                                        StartHigh = true;
                                        Edge1 += bitwidth;
                                        Edge1_2 += bitwidth;
                                        pts[0] = new PointF(startleft, StartHigh ? LowY : HighY);
                                        InitializePointArray(pts, 1, 16, pts[0]);
                                        pts[17] = new PointF(endright, StartHigh ? LowY : HighY);
                                    }
                                    else
                                    {
                                        if ((m_params.CompareType1.Value == CyECompareType.B_PWM__Equal &&
                                            (Compare1Value16 <= Compare2Value16)) ||
                                            (Compare1Value16 < Compare2Value16))
                                        {
                                            pts[0] = new PointF(startleft, LowY);
                                            pts[1] = new PointF(Edge2, LowY);
                                            pts[2] = new PointF(Edge2, HighY);
                                            pts[3] = new PointF(Edge4, HighY);
                                            pts[4] = new PointF(Edge4, LowY);
                                            pts[5] = new PointF(Edge2_2, LowY);
                                            pts[6] = new PointF(Edge2_2, HighY);
                                            pts[7] = new PointF(Edge4_2, HighY);
                                            pts[8] = new PointF(Edge4_2, LowY);
                                            pts[9] = new PointF(endright, LowY);
                                            InitializePointArray(pts, 10, 17, pts[9]);
                                        }
                                        else
                                        {
                                            pts[0] = new PointF(startleft, LowY);
                                            pts[1] = new PointF(endright, LowY);
                                            InitializePointArray(pts, 2, 17, pts[1]);
                                        }
                                    }
                                    break;
                            }
                        }
                        #endregion
                        #region PWM-CENTER
                        if (m_params.PwmMode.Value == CyEPwmMode.B_PWM__Center_Align)
                        {
                            //1 = _____|------|_____    = Greater Than
                            //2 = -----|______|-----    = Less Than
                            Edge1 = startleft + (bitwidth * (float)(CompareValue32));
                            Edge1_2 = startright + (bitwidth * (float)(CompareValue32));
                            Edge2 = startright - (bitwidth * (float)(CompareValue32));
                            Edge2_2 = endright - (bitwidth * (float)(CompareValue32));
                            //Get Compare Type Information for Compare Type 1
                            if (m_params.CompareType1.Value == CyECompareType.B_PWM__Less_Than ||
                                m_params.CompareType1.Value == CyECompareType.B_PWM__Less_Than_Or_Equal)
                            {
                                StartHigh = true;
                                if (m_params.CompareType1.Value == CyECompareType.B_PWM__Less_Than_Or_Equal)
                                {
                                    Edge1 += (bitwidth / 2f);
                                    Edge1_2 += (bitwidth / 2f);
                                    Edge2 -= (bitwidth / 2f);
                                    Edge2_2 -= (bitwidth / 2f);
                                    //Deal with half bit cycle if equal to period
                                    if (m_params.CompareValue1 == m_params.Period)
                                    {
                                        Edge1 -= (bitwidth / 2f);
                                        Edge1_2 -= (bitwidth / 2f);
                                        Edge2 += (bitwidth / 2f);
                                        Edge2_2 += (bitwidth / 2f);
                                    }
                                }
                                else
                                {
                                    Edge1 -= (bitwidth / 2f);
                                    Edge1_2 -= (bitwidth / 2f);
                                    Edge2 += (bitwidth / 2f);
                                    Edge2_2 += (bitwidth / 2f);
                                    //Deal with half bit cycle if equal to zero
                                    if (m_params.CompareValue1 == 0)
                                    {
                                        Edge1 += (bitwidth / 2f);
                                        Edge1_2 += (bitwidth / 2f);
                                        Edge2 -= (bitwidth / 2f);
                                        Edge2_2 -= (bitwidth / 2f);
                                    }
                                }

                                if ((CompareValue32 > PeriodValue32) ||
                                  ((CompareValue32 >= PeriodValue32) &&
                                    m_params.CompareType1.Value == CyECompareType.B_PWM__Less_Than_Or_Equal))
                                {
                                    pts[0] = new PointF(startleft, StartHigh ? HighY : LowY);
                                    InitializePointArray(pts, 1, 16, pts[0]);
                                    pts[17] = new PointF(endright, StartHigh ? HighY : LowY);
                                }
                                else
                                {
                                    pts[0] = new PointF(startleft, StartHigh ? HighY : LowY);
                                    pts[1] = new PointF(Edge1, StartHigh ? HighY : LowY);
                                    pts[2] = new PointF(Edge1, StartHigh ? LowY : HighY);
                                    pts[3] = new PointF(Edge2, StartHigh ? LowY : HighY);
                                    pts[4] = new PointF(Edge2, StartHigh ? HighY : LowY);
                                    pts[5] = new PointF(startright, StartHigh ? HighY : LowY);
                                    pts[6] = new PointF(startright, StartHigh ? HighY : LowY);
                                    pts[7] = new PointF(Edge1_2, StartHigh ? HighY : LowY);
                                    pts[8] = new PointF(Edge1_2, StartHigh ? LowY : HighY);
                                    pts[9] = new PointF(Edge2_2, StartHigh ? LowY : HighY);
                                    pts[10] = new PointF(Edge2_2, StartHigh ? HighY : LowY);
                                    pts[11] = new PointF(endright, StartHigh ? HighY : LowY);
                                    InitializePointArray(pts, 12, 17, pts[11]);
                                }
                            }
                            else if (m_params.CompareType1.Value == CyECompareType.B_PWM__Greater_Than ||
                                m_params.CompareType1.Value == CyECompareType.B_PWM__Greater_Than_Or_Equal_To ||
                                m_params.CompareType1.Value == CyECompareType.B_PWM__Firmware)
                            {
                                StartHigh = false;
                                if (m_params.CompareType1.Value == CyECompareType.B_PWM__Greater_Than_Or_Equal_To ||
                                    m_params.CompareType1.Value == CyECompareType.B_PWM__Firmware)
                                {
                                    Edge1 -= (bitwidth / 2f);
                                    Edge1_2 -= (bitwidth / 2f);
                                    Edge2 += (bitwidth / 2f);
                                    Edge2_2 += (bitwidth / 2f);
                                    if (m_params.CompareValue1 == 0)
                                    {
                                        Edge1 += (bitwidth / 2f);
                                        Edge1_2 += (bitwidth / 2f);
                                        Edge2 -= (bitwidth / 2f);
                                        Edge2_2 -= (bitwidth / 2f);
                                    }
                                }
                                else
                                {
                                    Edge1 += (bitwidth / 2f);
                                    Edge1_2 += (bitwidth / 2f);
                                    Edge2 -= (bitwidth / 2f);
                                    Edge2_2 -= (bitwidth / 2f);
                                    //Deal with half bit cycle if equal to period
                                    if (m_params.CompareValue1 == m_params.Period)
                                    {
                                        Edge1 -= (bitwidth / 2f);
                                        Edge1_2 -= (bitwidth / 2f);
                                        Edge2 += (bitwidth / 2f);
                                        Edge2_2 += (bitwidth / 2f);
                                    }
                                }

                                if ((CompareValue32 >= PeriodValue32 && m_params.CompareType1.Value ==
                                                                CyECompareType.B_PWM__Greater_Than) ||
                                     ((CompareValue32 > PeriodValue32) &&
                                     ((m_params.CompareType1.Value ==
                                                                CyECompareType.B_PWM__Greater_Than_Or_Equal_To) ||
                                     (m_params.CompareType1.Value == CyECompareType.B_PWM__Firmware))))
                                {
                                    pts[0] = new PointF(startleft, StartHigh ? HighY : LowY);
                                    InitializePointArray(pts, 1, 16, pts[0]);
                                    pts[17] = new PointF(endright, StartHigh ? HighY : LowY);
                                }
                                else
                                {
                                    pts[0] = new PointF(startleft, StartHigh ? HighY : LowY);
                                    pts[1] = new PointF(Edge1, StartHigh ? HighY : LowY);
                                    pts[2] = new PointF(Edge1, StartHigh ? LowY : HighY);
                                    if ((CompareValue32 == 0) &&
                                        ((m_params.CompareType1.Value ==
                                                            CyECompareType.B_PWM__Greater_Than_Or_Equal_To) ||
                                        (m_params.CompareType1.Value == CyECompareType.B_PWM__Firmware)))
                                    {
                                        pts[3] = new PointF(startright, StartHigh ? LowY : HighY);
                                    }
                                    else
                                    {
                                        pts[3] = new PointF(Edge2, StartHigh ? LowY : HighY);
                                    }
                                    pts[4] = new PointF(Edge2, StartHigh ? HighY : LowY);
                                    pts[5] = new PointF(startright, StartHigh ? HighY : LowY);
                                    pts[6] = new PointF(startright, StartHigh ? HighY : LowY);
                                    pts[7] = new PointF(Edge1_2, StartHigh ? HighY : LowY);
                                    pts[8] = new PointF(Edge1_2, StartHigh ? LowY : HighY);
                                    pts[9] = new PointF(Edge2_2, StartHigh ? LowY : HighY);
                                    pts[10] = new PointF(Edge2_2, StartHigh ? HighY : LowY);
                                    pts[11] = new PointF(endright, StartHigh ? HighY : LowY);
                                    InitializePointArray(pts, 12, 17, pts[11]);
                                }
                            }
                            else if ((CompareValue32 > PeriodValue32)
                                && (m_params.CompareType1.Value == CyECompareType.B_PWM__Equal))
                            {
                                StartHigh = true;
                                Edge1 += bitwidth;
                                Edge1_2 += bitwidth;
                                pts[0] = new PointF(startleft, StartHigh ? LowY : HighY);
                                InitializePointArray(pts, 1, 16, pts[0]);
                                pts[17] = new PointF(endright, StartHigh ? LowY : HighY);
                            }
                            else
                            {
                                if (m_params.CompareValue1 == m_params.Period)
                                {
                                    Edge1 -= (bitwidth / 2f);
                                    Edge2 = Edge1 + bitwidth;
                                    Edge3 = Edge2;
                                    Edge4 = Edge2;
                                    Edge1_2 -= (bitwidth / 2f);
                                    Edge2_2 = Edge1_2 + bitwidth;
                                    Edge3_2 = Edge2_2;
                                    Edge4_2 = Edge2_2;
                                }
                                else if (m_params.CompareValue1.HasValue && m_params.CompareValue1.Value == 0)
                                {
                                    Edge1 = startleft;
                                    Edge3 = startleft + (bitwidth / 2f);
                                    Edge2 = startright - (bitwidth / 2f);
                                    Edge4 = startright + (bitwidth / 2f);
                                    Edge1_2 = startright + (bitwidth / 2f);
                                    Edge3_2 = startright + (bitwidth / 2f);
                                    Edge2_2 = endright - (bitwidth / 2f);
                                    Edge4_2 = endright;
                                }
                                else
                                {
                                    StartHigh = false;
                                    Edge1 -= (bitwidth / 2f);
                                    Edge1_2 -= (bitwidth / 2f);
                                    Edge2 -= (bitwidth / 2f);
                                    Edge2_2 -= (bitwidth / 2f);
                                    Edge3 = Edge1 + bitwidth;
                                    Edge3_2 = Edge1_2 + bitwidth;
                                    Edge4 = Edge2 + bitwidth;
                                    Edge4_2 = Edge2_2 + bitwidth;
                                }
                                pts[0] = new PointF(startleft, LowY);
                                pts[1] = new PointF(Edge1, LowY);
                                pts[2] = new PointF(Edge1, HighY);
                                pts[3] = new PointF(Edge3, HighY);
                                pts[4] = new PointF(Edge3, LowY);
                                pts[5] = new PointF(Edge2, LowY);
                                pts[6] = new PointF(Edge2, HighY);
                                pts[7] = new PointF(Edge4, HighY);
                                pts[8] = new PointF(Edge4, LowY);
                                pts[9] = new PointF(Edge1_2, LowY);
                                pts[10] = new PointF(Edge1_2, HighY);
                                pts[11] = new PointF(Edge3_2, HighY);
                                pts[12] = new PointF(Edge3_2, LowY);
                                pts[13] = new PointF(Edge2_2, LowY);
                                pts[14] = new PointF(Edge2_2, HighY);
                                pts[15] = new PointF(Edge4_2, HighY);
                                pts[16] = new PointF(Edge4_2, LowY);
                                pts[17] = new PointF(endright, LowY);
                            }

                            if (StartHigh)
                            {
                                ptsDBph1[0] = new PointF(startleft, 1f);
                                ptsDBph1[1] = new PointF(Edge1, 1f);
                                ptsDBph1[2] = new PointF(Edge1, 0f);
                                ptsDBph1[3] = new PointF(Edge2 + dbcounts, 0f);
                                ptsDBph1[4] = new PointF(Edge2 + dbcounts, 1f);
                                ptsDBph1[5] = new PointF(startright, 1f);
                                ptsDBph1[6] = new PointF(startright, 1f);
                                ptsDBph1[7] = new PointF(Edge1_2, 1f);
                                ptsDBph1[8] = new PointF(Edge1_2, 0f);
                                ptsDBph1[9] = new PointF(Edge2_2 + dbcounts, 0f);
                                ptsDBph1[10] = new PointF(Edge2_2 + dbcounts, 1f);
                                ptsDBph1[11] = new PointF(endright, 1f);
                                ptsDBph2[0] = new PointF(startleft, 0f);
                                ptsDBph2[1] = new PointF(Edge1 + dbcounts, 0f);
                                ptsDBph2[2] = new PointF(Edge1 + dbcounts, 1f);
                                ptsDBph2[3] = new PointF(Edge2, 1f);
                                ptsDBph2[4] = new PointF(Edge2, 0f);
                                ptsDBph2[5] = new PointF(startright, 0f);
                                ptsDBph2[6] = new PointF(startright, 0f);
                                ptsDBph2[7] = new PointF(Edge1_2 + dbcounts, 0f);
                                ptsDBph2[8] = new PointF(Edge1_2 + dbcounts, 1f);
                                ptsDBph2[9] = new PointF(Edge2_2, 1f);
                                ptsDBph2[10] = new PointF(Edge2_2, 0f);
                                ptsDBph2[11] = new PointF(endright, 0f);
                            }
                            else
                            {
                                ptsDBph1[0] = new PointF(startleft, 0f);
                                ptsDBph1[1] = new PointF(Edge1 + dbcounts, 0f);
                                ptsDBph1[2] = new PointF(Edge1 + dbcounts, 1f);
                                ptsDBph1[3] = new PointF(Edge2, 1f);
                                ptsDBph1[4] = new PointF(Edge2, 0f);
                                ptsDBph1[5] = new PointF(startright, 0f);
                                ptsDBph1[6] = new PointF(startright, 0f);
                                ptsDBph1[7] = new PointF(Edge1_2 + dbcounts, 0f);
                                ptsDBph1[8] = new PointF(Edge1_2 + dbcounts, 1f);
                                ptsDBph1[9] = new PointF(Edge2_2, 1f);
                                ptsDBph1[10] = new PointF(Edge2_2, 0f);
                                ptsDBph1[11] = new PointF(endright, 0f);
                                ptsDBph2[0] = new PointF(startleft, 1f);
                                ptsDBph2[1] = new PointF(Edge1, 1f);
                                ptsDBph2[2] = new PointF(Edge1, 0f);
                                ptsDBph2[3] = new PointF(Edge2 + dbcounts, 0f);
                                ptsDBph2[4] = new PointF(Edge2 + dbcounts, 1f);
                                ptsDBph2[5] = new PointF(startright, 1f);
                                ptsDBph2[6] = new PointF(startright, 1f);
                                ptsDBph2[7] = new PointF(Edge1_2, 1f);
                                ptsDBph2[8] = new PointF(Edge1_2, 0f);
                                ptsDBph2[9] = new PointF(Edge2_2 + dbcounts, 0f);
                                ptsDBph2[10] = new PointF(Edge2_2 + dbcounts, 1f);
                                ptsDBph2[11] = new PointF(endright, 1f);
                            }
                        }
                        #endregion
                        #region PWM-HARDWARE
                        if (m_params.PwmMode.Value == CyEPwmMode.B_PWM__HardwareSelect)
                        {
                            Edge1 = (2 * PB_EXTENTS_BORDER) + PB_PWMTEXT_WIDTH;
                            pts[0] = new PointF(0f, 0f);
                            InitializePointArray(pts, 1, 17, pts[0]);
                            ptsDBph1[0] = new PointF(0f, 0f);
                            InitializePointArray(ptsDBph1, 1, 11, ptsDBph1[0]);
                            ptsDBph2[0] = new PointF(0f, 0f);
                            InitializePointArray(ptsDBph2, 1, 11, ptsDBph2[0]);
                        }
                        #endregion
                        #region PWM-DITHER
                        if (m_params.PwmMode.Value == CyEPwmMode.B_PWM__Dither)
                        {
                            Edge1 = startleft + (bitwidth * (float)(PeriodValue32 - CompareValue32 + 1));
                            Edge1_2 = startright + (bitwidth * (float)(PeriodValue32 - CompareValue32 + 1));
                            Edge2 = Edge1 - bitwidth;
                            Edge2_2 = Edge1_2 - bitwidth;

                            StartHigh = (m_params.CompareType1.Value == CyECompareType.B_PWM__Greater_Than ||
                                m_params.CompareType1.Value == CyECompareType.B_PWM__Greater_Than_Or_Equal_To ||
                                m_params.CompareType1.Value == CyECompareType.B_PWM__Firmware); // Left Aligned 

                            if (CompareValue32 > PeriodValue32)
                            {
                                StartHigh = true;
                                Edge1 += bitwidth;
                                Edge1_2 += bitwidth;
                                pts[0] = new PointF(startleft, StartHigh ? LowY : HighY);
                                InitializePointArray(pts, 1, 16, pts[0]);
                                pts[17] = new PointF(endright, StartHigh ? LowY : HighY);
                            }
                            else
                            {
                                pts[0] = new PointF(startleft, StartHigh ? HighY : LowY);
                                pts[1] = new PointF(Edge1, StartHigh ? HighY : LowY);
                                pts[2] = new PointF(Edge1, StartHigh ? LowY : HighY);
                                pts[3] = new PointF(Edge2, StartHigh ? LowY : HighY);
                                pts[4] = new PointF(Edge2, StartHigh ? HighY : LowY);
                                pts[5] = new PointF(Edge1, StartHigh ? HighY : LowY);
                                pts[6] = new PointF(Edge1, StartHigh ? LowY : HighY);
                                pts[7] = new PointF(startright, StartHigh ? LowY : HighY);
                                pts[8] = new PointF(startright, StartHigh ? HighY : LowY);
                                pts[9] = new PointF(Edge1_2, StartHigh ? HighY : LowY);
                                pts[10] = new PointF(Edge1_2, StartHigh ? LowY : HighY);
                                pts[11] = new PointF(Edge2_2, StartHigh ? LowY : HighY);
                                pts[12] = new PointF(Edge2_2, StartHigh ? HighY : LowY);
                                pts[13] = new PointF(Edge1_2, StartHigh ? HighY : LowY);
                                pts[14] = new PointF(Edge1_2, StartHigh ? LowY : HighY);
                                pts[15] = new PointF(endright, StartHigh ? LowY : HighY);
                                pts[16] = new PointF(endright, StartHigh ? LowY : HighY);
                                pts[17] = new PointF(endright, StartHigh ? LowY : HighY);
                            }
                            PointF[] pts2 = new PointF[4];
                            pts2[0] = pts[1];
                            pts2[1] = pts[2];
                            pts2[2] = pts[3];
                            pts2[3] = pts[4];
                            wfg.FillPolygon(redbrush, pts2);
                            pts2[0] = pts[9];
                            pts2[1] = pts[10];
                            pts2[2] = pts[11];
                            pts2[3] = pts[12];
                            wfg.FillPolygon(redbrush, pts2);
                            if (StartHigh)
                            {
                                if ((startleft + dbcounts) < Edge1)
                                {
                                    ptsDBph1[0] = new PointF(startleft, 0f);
                                    ptsDBph1[1] = new PointF(startleft + dbcounts, 0f);
                                    ptsDBph1[2] = new PointF(startleft + dbcounts, 1f);
                                    ptsDBph1[3] = new PointF(Edge1, 1f);
                                    ptsDBph1[4] = new PointF(Edge1, 0f);
                                    ptsDBph1[5] = new PointF(startright, 0f);
                                    ptsDBph1[6] = new PointF(startright, 0f);
                                    ptsDBph1[7] = new PointF(startright + dbcounts, 0f);
                                    ptsDBph1[8] = new PointF(startright + dbcounts, 1f);
                                    ptsDBph1[9] = new PointF(Edge1_2, 1f);
                                    ptsDBph1[10] = new PointF(Edge1_2, 0f);
                                    ptsDBph1[11] = new PointF(endright, 0f);
                                }
                                else
                                {
                                    ptsDBph1[0] = new PointF(startleft, 0f);
                                    ptsDBph1[1] = new PointF(endright, 0f);
                                    InitializePointArray(ptsDBph1, 2, 11, ptsDBph1[1]);
                                }

                                if ((Edge1 + dbcounts) < startright)
                                {
                                    ptsDBph2[0] = new PointF(startleft, 0f);
                                    ptsDBph2[1] = new PointF(Edge1 + dbcounts, 0f);
                                    ptsDBph2[2] = new PointF(Edge1 + dbcounts, 1f);
                                    ptsDBph2[3] = new PointF(startright, 1f);
                                    ptsDBph2[4] = new PointF(startright, 0f);
                                    ptsDBph2[5] = new PointF(Edge1_2 + dbcounts, 0f);
                                    ptsDBph2[6] = new PointF(Edge1_2 + dbcounts, 1f);
                                    ptsDBph2[7] = new PointF(endright, 1f);
                                    ptsDBph2[8] = new PointF(endright, 1f);
                                    ptsDBph2[9] = new PointF(endright, 1f);
                                    ptsDBph2[10] = new PointF(endright, 1f);
                                    ptsDBph2[11] = new PointF(endright, 1f);
                                }
                                else
                                {
                                    ptsDBph2[0] = new PointF(startleft, 0f);
                                    ptsDBph2[1] = new PointF(endright, 0f);
                                    InitializePointArray(ptsDBph2, 2, 11, ptsDBph1[1]);
                                }
                            }
                            else
                            {
                                if ((Edge1 + dbcounts) > startright)
                                {
                                    ptsDBph1[0] = new PointF(startleft, 0f);
                                    ptsDBph1[1] = new PointF(endright, 0f);
                                    InitializePointArray(ptsDBph1, 2, 11, ptsDBph1[1]);
                                }
                                else
                                {
                                    ptsDBph1[0] = new PointF(startleft, 0f);
                                    ptsDBph1[1] = new PointF(Edge1 + dbcounts, 0f);
                                    ptsDBph1[2] = new PointF(Edge1 + dbcounts, 1f);
                                    ptsDBph1[3] = new PointF(startright, 1f);
                                    ptsDBph1[4] = new PointF(startright, 0f);
                                    ptsDBph1[5] = new PointF(Edge1_2 + dbcounts, 0f);
                                    ptsDBph1[6] = new PointF(Edge1_2 + dbcounts, 1f);
                                    ptsDBph1[7] = new PointF(endright, 1f);
                                    ptsDBph1[8] = new PointF(endright, 1f);
                                    ptsDBph1[9] = new PointF(endright, 1f);
                                    ptsDBph1[10] = new PointF(endright, 1f);
                                    ptsDBph1[11] = new PointF(endright, 1f);
                                }

                                if ((startleft + dbcounts) < Edge1)
                                {
                                    ptsDBph2[0] = new PointF(startleft, 0f);
                                    ptsDBph2[1] = new PointF(startleft + dbcounts, 0f);
                                    ptsDBph2[2] = new PointF(startleft + dbcounts, 1f);
                                    ptsDBph2[3] = new PointF(Edge1, 1f);
                                    ptsDBph2[4] = new PointF(Edge1, 0f);
                                    ptsDBph2[5] = new PointF(startright, 0f);
                                    ptsDBph2[6] = new PointF(startright, 0f);
                                    ptsDBph2[7] = new PointF(startright + dbcounts, 0f);
                                    ptsDBph2[8] = new PointF(startright + dbcounts, 1f);
                                    ptsDBph2[9] = new PointF(Edge1_2, 1f);
                                    ptsDBph2[10] = new PointF(Edge1_2, 0f);
                                    ptsDBph2[11] = new PointF(endright, 0f);
                                }
                                else
                                {
                                    ptsDBph2[0] = new PointF(startleft, 0f);
                                    ptsDBph2[1] = new PointF(endright, 0f);
                                    InitializePointArray(ptsDBph2, 2, 11, ptsDBph2[1]);
                                }
                            }
                        }
                        break;
                        #endregion
                    #endregion
                    #region PH1
                    case PH1:
                        int j = 0;
                        foreach (PointF p in ptsDBph1)
                        {
                            if (p.Y == 0f)
                                pts[j++] = new PointF(p.X, LowY);
                            else
                                pts[j++] = new PointF(p.X, HighY);
                        }
                        InitializePointArray(pts, 12, 17, pts[11]);

                        //Check to see if any errors where X2 is less than X1
                        for (j = 0; j < pts.Length - 1; j++)
                        {
                            if (pts[j + 1].X < pts[j].X)
                            {
                                pts[0] = new PointF(startleft, LowY);
                                pts[1] = new PointF(endright, LowY);
                                InitializePointArray(pts, 2, 17, pts[1]);
                                break;
                            }
                        }
                        break;
                    #endregion
                    #region PH2
                    case PH2:
                        int k = 0;
                        foreach (PointF p in ptsDBph2)
                        {
                            if (p.Y == 0f)
                                pts[k++] = new PointF(p.X, LowY);
                            else
                                pts[k++] = new PointF(p.X, HighY);
                        }
                        InitializePointArray(pts, 12, 17, pts[11]);

                        //Check to see if any errors where X2 is less than X1
                        for (k = 0; k < pts.Length - 1; k++)
                        {
                            if (pts[k + 1].X < pts[k].X)
                            {
                                pts[0] = new PointF(startleft, LowY);
                                pts[1] = new PointF(endright, LowY);
                                InitializePointArray(pts, 2, 17, pts[1]);
                                break;
                            }
                        }
                        break;
                    #endregion
                }
                //Draw the Waveform
                SolidBrush wfbrush = new SolidBrush(Color.Blue);
                Pen wfPen = new Pen(wfbrush);
                wfg.DrawLines(wfPen, pts);
            }
            wfg.Dispose();
            blkbrush.Dispose();
            whitebrush.Dispose();
            greybrush.Dispose();
            redbrush.Dispose();

            m_pbDrawing.Image = waveform;
        }
        #endregion
    }
}
