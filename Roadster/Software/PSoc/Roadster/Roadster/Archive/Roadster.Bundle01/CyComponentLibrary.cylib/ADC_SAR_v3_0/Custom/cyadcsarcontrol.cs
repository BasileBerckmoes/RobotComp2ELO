/*******************************************************************************
* Copyright 2008-2014, Cypress Semiconductor Corporation.  All rights reserved.
* You may use this file only in accordance with the license, terms, conditions, 
* disclaimers, and limitations in the end user license agreement accompanying  
* the software package with which this file was provided.   
********************************************************************************/

using System;
using System.Collections.Generic;
using System.Windows.Forms;
using CyDesigner.Extensions.Common;
using CyDesigner.Extensions.Gde;
using System.Drawing;
using System.Diagnostics;

namespace ADC_SAR_v3_0
{
    public partial class CyConfigureTab : UserControl, ICyParamEditingControl
    {
        #region Enumerated Type String Names
        public static string RANGE_VDDA = "Vdda";
        public static string RANGE_VDAC = "VDAC";
        public static string REF_INTERNAL_REF = "Internal Vref";
        #endregion

        #region References to Enum Type String Names
        private const string REF_EXTERNAL = "External Vref";
        #endregion

        private CyParameters m_params;
        private double m_clockValue = 0;
        private uint m_previousConversionRate = 0;
        private CyEAdcRefType m_previousReference;
        private bool m_referenceComboBoxUpdateLocked = false;
        private enum CyEOnErrorBehavior { ReduceConversionRate, ShowError }

        #region Constructor(s)
        public CyConfigureTab(CyParameters inst)
        {
            m_params = inst;
            m_params.m_configureTab = this;

            InitializeComponent();
            this.Dock = DockStyle.Fill;

            m_previousConversionRate = m_params.SampleRateDefault;

            // Create NumericUpDown TextChange Event Handlers
            numSampleRate.TextChanged += new EventHandler(numSampleRate_TextChanged);
            numRefVoltage.TextChanged += new EventHandler(numRefVoltage_TextChanged);

            // Completion of ComboBoxes
            cbResolution.DataSource = m_params.m_resolutionList;
            foreach (string item in m_params.m_referenceList)
            {
                cbReference.Items.Add(item);
            }
            cbInputRange.DataSource = m_params.m_inputRangeList;
            numSampleRate.Minimum = 0;
            numSampleRate.Maximum = uint.MaxValue;
            numRefVoltage.Minimum = decimal.MinValue;
            numRefVoltage.Maximum = decimal.MaxValue;
        }
        #endregion

        #region ICyParamEditingControl Members
        public Control DisplayControl
        {
            get { return this; }
        }

        public IEnumerable<CyCustErr> GetErrors()
        {
            List<CyCustErr> errs = new List<CyCustErr>();

            // Check error providers on GUI
            if (errorProvider != null)
                errs.AddRange(CheckControlForErrors(this.Controls));

            // Check symbol parameters validators
            foreach (string paramName in m_params.InstQuery.GetParamNames())
            {
                CyCompDevParam param = m_params.InstQuery.GetCommittedParam(paramName);
                if (param.TabName.Equals(CyCustomizer.CONFIGURE_TAB_NAME) && param.ErrorCount > 0)
                {
                    foreach (string errMsg in param.Errors)
                        errs.Add(new CyCustErr(errMsg));
                }
            }

            return errs;
        }
        #endregion

        #region Assigning parameters values to controls
        public void UpdateUI()
        {
            // Resolution
            cbResolution.SelectedItem = Convert.ToByte(m_params.AdcResolution).ToString();
            // Reference
            cbReference.SelectedItem = CyDictParser.GetDictValue(m_params.m_dnDict, m_params.AdcReference);
            // Input Range
            cbInputRange.SelectedItem = CyDictParser.GetDictValue(m_params.m_dnDict, m_params.AdcInputRange);
            // Voltage Reference
            numRefVoltage.Text = m_params.RefVoltage.ToString();
            // Sample Mode
            switch (m_params.AdcSampleMode)
            {
                case CyEAdcSampleModeType.Free_Running:
                    rbFreeRunning.Checked = true;
                    break;
                case CyEAdcSampleModeType.Software_Trigger:
                    rbSoftwareTrigerr.Checked = true;
                    break;
                case CyEAdcSampleModeType.Hardware_Trigger:
                    m_rbHardwareTrigerr.Checked = true;
                    break;
                default:
                    break;
            }

            // Clock Source
            if (m_params.AdcClockSource == CyEAdcClockSrcType.Internal)
            {
                rbInternal.Checked = true;
            }
            else
            {
                rbExternal.Checked = true;
            }
            // Enable next_out
            chbNextOut.Checked = m_params.EnableNextOut;
            // Clock Frequency
            UpdateClockData();

            ValidateSampleRate(m_params.AdcSampleRate, CyEOnErrorBehavior.ShowError);
            ValidateReference(CyEOnErrorBehavior.ShowError);
        }

        private void FillReferenceComboBox()
        {
            FillReferenceComboBox(String.Empty, String.Empty);
        }
        private void FillReferenceComboBox(string itemToRemove, string newItem)
        {
            m_referenceComboBoxUpdateLocked = true;
            object selectedItem = cbReference.SelectedItem;
            cbReference.Items.Clear();
            foreach (string item in m_params.m_referenceList)
            {
                if (item != itemToRemove)
                    cbReference.Items.Add(item);
            }
            if (selectedItem != null)
            {
                if (cbReference.Items.Contains(selectedItem))
                    cbReference.SelectedItem = selectedItem;
                else
                    cbReference.SelectedItem = newItem;
            }
            m_referenceComboBoxUpdateLocked = false;
        }
        #endregion

        #region Assigning controls values to parameters
        private void SetResolution()
        {
            try
            {
                m_params.AdcResolution = (CyEAdcResolution)byte.Parse(cbResolution.Text);
            }
            catch (Exception) { }
        }

        private void SetInputRange()
        {
            m_params.AdcInputRange = (CyEAdcInputRangeType)CyDictParser.GetDictKey(m_params.m_dnDict,
                cbInputRange.Text);
        }

        private void SetReference()
        {
            m_params.AdcReference = (CyEAdcRefType)CyDictParser.GetDictKey(m_params.m_dnDict, cbReference.Text);
        }

        private void SetVoltageReference()
        {
            try
            {
                m_params.RefVoltage = double.Parse(numRefVoltage.Text);
            }
            catch (Exception) { }
        }

        private void SetSampleMode()
        {
            if (rbFreeRunning.Checked)
                m_params.AdcSampleMode = CyEAdcSampleModeType.Free_Running;
            else if (rbSoftwareTrigerr.Checked)
                m_params.AdcSampleMode = CyEAdcSampleModeType.Software_Trigger;
            else
                m_params.AdcSampleMode = CyEAdcSampleModeType.Hardware_Trigger;
        }

        private void SetClockSource()
        {
            m_params.AdcClockSource = rbInternal.Checked ? CyEAdcClockSrcType.Internal
                : CyEAdcClockSrcType.External;
        }
        #endregion

        #region Errors handling
        private List<CyCustErr> CheckControlForErrors(ControlCollection controls)
        {
            string errorMessage = String.Empty;
            List<CyCustErr> errs = new List<CyCustErr>();
            foreach (Control control in controls)
            {
                if (control.Visible)
                {
                    errorMessage = errorProvider.GetError(control);
                    if (String.IsNullOrEmpty(errorMessage) == false)
                        errs.Add(new CyCustErr(errorMessage));
                    // Recursively call itself again to make sure that nested controls does not contain errors
                    if (control.Controls.Count > 0)
                        errs.AddRange(CheckControlForErrors(control.Controls));
                }
            }
            return errs;
        }

        public void ShowError(string paramName, CyCustErr err)
        {
            Control control = null;
            string errMsg = (err != null && err.IsOk) ? String.Empty : err.Message;
            switch (paramName)
            {
                case CyParamNames.ADC_CLOCK:
                    control = rbInternal;
                    break;
                case CyParamNames.ADC_INPUT_RANGE:
                    control = cbInputRange;
                    break;
                case CyParamNames.ADC_REFERENCE:
                    control = cbReference;
                    break;
                case CyParamNames.ADC_RESOLUTION:
                    control = cbResolution;
                    break;
                case CyParamNames.ADC_SAMPLE_MODE:
                    control = rbFreeRunning;
                    break;
                case CyParamNames.REF_VOLTAGE:
                    control = numRefVoltage;
                    break;
                case CyParamNames.SAMPLE_RATE:
                    // Need to check this control one more time because setting parameter on load 
                    // is fine and error message may be overwritten by empty one
                    control = numSampleRate;
                    uint value = 0;
                    uint.TryParse(control.Text, out value);
                    if (value < m_params.GetMinSampleRate() || value > m_params.GetMaxSampleRate())
                    {
                        errorProvider.SetError(control, String.Format(Resources.ConversionRate,
                            m_params.GetMinSampleRate(), m_params.GetMaxSampleRate()));
                        return;
                    }
                    if (ValidateReference(CyEOnErrorBehavior.ShowError) == false)
                        return;
                    break;
                default:
                    break;
            }
            if (control != null)
                errorProvider.SetError(control, errMsg);
        }
        #endregion

        #region Event Handlers
        private void CyConfigureTab_Load(object sender, EventArgs e)
        {
            uint value = 0;
            uint.TryParse(numSampleRate.Text, out value);
            m_params.AdcSampleRate = value;
            ValidateSampleRate(value, CyEOnErrorBehavior.ShowError);

            // Voltage Reference control have to be updated on load because system VDDA could change
            UpdateRefVoltageControl();
        }

        private void cbResolution_SelectedIndexChanged(object sender, EventArgs e)
        {
            SetResolution();
            UpdateClockData();
            UpdateSampleRateData();
            SetCorrectSampleRate();
        }

        private void numSampleRate_TextChanged(object sender, EventArgs e)
        {
            NumericUpDown currentNumeric = (NumericUpDown)sender;
            uint value = 0;
            uint.TryParse(currentNumeric.Text, out value);

            m_params.AdcSampleRate = value;
            ValidateSampleRate(value, CyEOnErrorBehavior.ShowError);
            m_clockValue = m_params.GetInternalFreq();
            UpdateClockData();
        }

        private void cbInputRange_SelectedIndexChanged(object sender, EventArgs e)
        {
            SetInputRange();
            UpdateRefVoltageControl();
            UpdateReferenceCombobox(sender);
            SetCorrectSampleRate();
            numRefVoltage_TextChanged(numRefVoltage, new EventArgs());
        }

        private void cbReference_SelectedIndexChanged(object sender, EventArgs e)
        {
            SetReference();
            UpdateReferenceCombobox(sender);
            UpdateRefVoltageControl();
            numSampleRate_TextChanged(numSampleRate, e);
            numRefVoltage_TextChanged(numRefVoltage, new EventArgs());
            m_previousReference = m_params.AdcReference;
            SetCorrectSampleRate();
        }

        private void SetCorrectSampleRate()
        {
            if (m_params.GlobalEditMode == false) return;

            if (m_params.AdcReference == CyEAdcRefType.Int_Ref_Not_Bypassed)
            {
                ValidateReference(CyEOnErrorBehavior.ReduceConversionRate);
            }
            else
            {
                uint maxSampleRate = m_params.GetMaxSampleRate();
                uint minSampleRate = m_params.GetMinSampleRate();
                if (m_params.AdcSampleRate > maxSampleRate)
                {
                    numSampleRate.Value = maxSampleRate;
                }
                else if (m_params.AdcSampleRate < minSampleRate)
                {
                    numSampleRate.Value = minSampleRate;
                }
            }
        }

        private void numRefVoltage_TextChanged(object sender, EventArgs e)
        {
            NumericUpDown currentNumeric = (NumericUpDown)sender;
            double value = 0;
            double.TryParse(currentNumeric.Text, out value);

            double maxVoltage;
            string message;
            // External voltage reference should be limited to Vdda/2 for "Vssa to Vdda(Single)" 
            // and "0.0 +/- Vdda/2(Differential)" input ranges
            if (m_params.AdcReference == CyEAdcRefType.Ext_Ref &&
                (m_params.AdcInputRange == CyEAdcInputRangeType.Vssa_to_Vdda ||
                m_params.AdcInputRange == CyEAdcInputRangeType.Vneg_Vdda_2_Diff))
            {
                maxVoltage = m_params.m_systemVdda / 2;
                message = Resources.VoltageReferenceVddaDiv2;
            }
            else
            {
                maxVoltage = m_params.m_systemVdda;
                message = Resources.VoltageReference;
            }

            if (value < CyParamRange.REF_VOLTAGE_MIN || value > maxVoltage)
            {
                errorProvider.SetError(currentNumeric, String.Format(message, CyParamRange.REF_VOLTAGE_MIN,
                    maxVoltage));
            }
            else
            {
                errorProvider.SetError(currentNumeric, String.Empty);
                SetVoltageReference();
            }
        }

        // Sample Mode
        private void rbSampleMode_CheckedChanged(object sender, EventArgs e)
        {
            SetSampleMode();
        }

        // Clock source radio buttons
        private void rbInternal_CheckedChanged(object sender, EventArgs e)
        {
            SetClockSource();
            if (rbInternal.Checked)
            {
                m_clockValue = m_params.GetInternalFreq();
                if (m_params.AdcSampleRate < m_params.GetMinSampleRate() || m_params.AdcSampleRate >
                    m_params.GetMaxSampleRate())
                    m_params.AdcSampleRate = m_previousConversionRate;
            }
            else
            {
                m_clockValue = m_params.m_externalClockInKHz;
                if (m_params.AdcSampleRate >= m_params.GetMinSampleRate() && m_params.AdcSampleRate <=
                    m_params.GetMaxSampleRate())
                    m_previousConversionRate = m_params.AdcSampleRate;
            }
            UpdateClockData();
            UpdateSampleRateData();
            ValidateReference(CyEOnErrorBehavior.ShowError);
        }

        private void tbClockFreq_TextChanged(object sender, EventArgs e)
        {
            double clock = m_params.AdcClockSource == CyEAdcClockSrcType.External
                ? m_params.m_externalClockInKHz : m_clockValue;
            if ((clock < CyParamRange.MIN_FREQ_KHZ) || (clock > m_params.MaxClockFrequencyKHz))
            {
                errorProvider.SetError((TextBox)sender, String.Format(Resources.ClockFrequency,
                    CyParamRange.MIN_FREQ_MHZ, m_params.MaxClockFrequencyMHz));
            }
            else
            {
                errorProvider.SetError((TextBox)sender, String.Empty);
            }
        }

        private void chbNextOut_CheckedChanged(object sender, EventArgs e)
        {
            CheckBox control = (CheckBox)sender;
            m_params.EnableNextOut = chbNextOut.Checked;
        }
        #endregion

        #region Validation methods
        private void ValidateSampleRate(uint value, CyEOnErrorBehavior onErrorBehavior)
        {
            if (value < m_params.GetMinSampleRate() || value > m_params.GetMaxSampleRate())
            {
                switch (onErrorBehavior)
                {
                    case CyEOnErrorBehavior.ReduceConversionRate:
                        numSampleRate.Value = m_params.GetMaxSampleRate();
                        break;
                    case CyEOnErrorBehavior.ShowError:
                        errorProvider.SetError(numSampleRate, String.Format(Resources.ConversionRate,
                        m_params.GetMinSampleRate(), m_params.GetMaxSampleRate()));
                        break;
                    default:
                        Debug.Assert(false);
                        break;
                }
            }
            else
            {
                errorProvider.SetError(numSampleRate, String.Empty);
            }
            ValidateReference(onErrorBehavior);
        }

        private bool ValidateReference(CyEOnErrorBehavior onErrorBehavior)
        {
            uint maxSampleRate = m_params.GetMaxSampleRateForInternalVref();
            uint minSampleRate = m_params.GetMinSampleRate();
            if (m_params.AdcReference == CyEAdcRefType.Int_Ref_Not_Bypassed &&
                m_params.AdcClockSource == CyEAdcClockSrcType.Internal &&
                (m_params.AdcSampleRate < minSampleRate || m_params.AdcSampleRate > maxSampleRate))
            {
                switch (onErrorBehavior)
                {
                    case CyEOnErrorBehavior.ReduceConversionRate:
                        errorProvider.SetError(cbReference, String.Empty);
                        errorProvider.SetError(numSampleRate, String.Empty);
                        if (m_params.AdcSampleRate < minSampleRate)
                            numSampleRate.Value = minSampleRate;
                        else if (m_params.AdcSampleRate > maxSampleRate)
                            numSampleRate.Value = maxSampleRate;
                        break;
                    case CyEOnErrorBehavior.ShowError:
                        string message = m_params.GetInvalidConvRateIntVrefMessage();
                        errorProvider.SetError(cbReference, String.Format(message, maxSampleRate));
                        errorProvider.SetError(numSampleRate, String.Format(message, maxSampleRate));
                        break;
                    default:
                        Debug.Assert(false);
                        break;
                }
                return false;
            }
            else if (m_params.AdcReference == CyEAdcRefType.Int_Ref_Bypass &&
                (m_params.AdcInputRange == CyEAdcInputRangeType.Vneg_Vdda_Diff))
            {
                string currentInputRange = CyDictParser.GetDictValue(m_params.m_dnDict, m_params.AdcInputRange);
                errorProvider.SetError(cbReference, string.Format(Resources.VddaInternalBypass,
                    currentInputRange.Substring(0, currentInputRange.IndexOf('(') - 1)));
                return false;
            }
            else if (m_params.AdcReference == CyEAdcRefType.Ext_Ref &&
                (m_params.AdcInputRange == CyEAdcInputRangeType.Vneg_VDAC_Diff ||
                m_params.AdcInputRange == CyEAdcInputRangeType.Vssa_to_VDAC))
            {
                string currentInputRange = CyDictParser.GetDictValue(m_params.m_dnDict, m_params.AdcInputRange);
                errorProvider.SetError(cbReference, string.Format(Resources.VDACExternalRef,
                    currentInputRange.Substring(0, currentInputRange.IndexOf('(') - 1)));
                return false;
            }
            else
            {
                errorProvider.SetError(cbReference, String.Empty);
                if (m_params.AdcSampleRate >= m_params.GetMinSampleRate() &&
                    m_params.AdcSampleRate <= m_params.GetMaxSampleRate())
                    errorProvider.SetError(numSampleRate, String.Empty);
                return true;
            }
        }

        private void UpdateReferenceCombobox(object sender)
        {
            if (m_referenceComboBoxUpdateLocked) return;

            string extRefItem = CyDictParser.GetDictValue(m_params.m_dnDict, CyEAdcRefType.Ext_Ref);
            string bypassRefItem = CyDictParser.GetDictValue(m_params.m_dnDict, CyEAdcRefType.Int_Ref_Bypass);
            string internalRefItem = CyDictParser.GetDictValue(m_params.m_dnDict, CyEAdcRefType.Int_Ref_Not_Bypassed);
            string previouslySelectedItem = extRefItem;
            CyEAdcRefType referenceSelectedItem = CyEAdcRefType.Int_Ref_Not_Bypassed;
            CyEAdcInputRangeType inputRangeSelectedItem = CyEAdcInputRangeType.Vneg_VDAC_Diff;

            if (cbReference.SelectedItem != null)
            {
                referenceSelectedItem = (CyEAdcRefType)CyDictParser.GetDictKey(m_params.m_dnDict,
                    cbReference.SelectedItem.ToString());
            }
            if (cbInputRange.SelectedItem != null)
            {
                inputRangeSelectedItem = (CyEAdcInputRangeType)CyDictParser.GetDictKey(m_params.m_dnDict,
                    cbInputRange.SelectedItem.ToString());
            }

            if (inputRangeSelectedItem == CyEAdcInputRangeType.Vneg_Vdda_Diff)
            {
                if (m_params.GlobalEditMode)
                {
                    // Remove the item if Input Range was changed or if any different from Internal Bypassed 
                    // value was selected in Reference combobox.
                    if (cbReference.SelectedItem.ToString() != CyDictParser.GetDictValue(m_params.m_dnDict,
                        m_previousReference) || sender == cbInputRange)
                    {
                        if (cbReference.Items.Contains(bypassRefItem))
                        {
                            FillReferenceComboBox(bypassRefItem, internalRefItem);
                        }
                    }
                }
                else
                {
                    if (cbReference.Items.Contains(bypassRefItem) && (referenceSelectedItem !=
                        CyEAdcRefType.Int_Ref_Bypass))
                    {
                        FillReferenceComboBox(bypassRefItem, internalRefItem);
                    }
                }
            }
            else if (inputRangeSelectedItem == CyEAdcInputRangeType.Vneg_VDAC_Diff || inputRangeSelectedItem ==
                CyEAdcInputRangeType.Vssa_to_VDAC)
            {
                if (m_params.GlobalEditMode)
                {
                    // Remove the item if Input Range was changed or if any different from External 
                    // value was selected in Reference combobox.
                    if (cbReference.SelectedItem.ToString() != CyDictParser.GetDictValue(m_params.m_dnDict,
                        m_previousReference) || sender == cbInputRange)
                    {
                        if (cbReference.Items.Contains(extRefItem))
                        {
                            FillReferenceComboBox(extRefItem, bypassRefItem);
                        }
                    }
                }
                else
                {
                    if (cbReference.Items.Contains(extRefItem) && (referenceSelectedItem != CyEAdcRefType.Ext_Ref))
                    {
                        FillReferenceComboBox(extRefItem, bypassRefItem);
                    }
                }
            }
            else
            {
                FillReferenceComboBox();
            }
        }
        #endregion

        #region Updating Clock and Sample Rate controls and labels
        public void UpdateClockData()
        {
            if (m_params.AdcClockSource == CyEAdcClockSrcType.External)
            {
                bool vis = m_params.m_externalClockInKHz >= 0;
                tbClockFreq.Visible = vis;
                lblNoFreq.Visible = !vis;
                tbClockFreq.Text = Math.Round(m_params.m_externalClockInKHz, 3).ToString();
                lblConversionRateLabel.Enabled = false;
                lblActualConversionRate.Enabled = false;
                if (lblNoFreq.Visible)
                {
                    lblActualConversionRate.Font = new System.Drawing.Font(lblActualConversionRate.Font.FontFamily,
                    lblActualConversionRate.Font.Size, (FontStyle.Bold | FontStyle.Italic));
                    lblActualConversionRate.Text = lblNoRate.Text;
                }
                else
                {
                    try
                    {
                        if (Convert.ToDouble(numSampleRate.Text) > 0)
                        {
                            lblActualConversionRate.Font = new System.Drawing.Font(
                                lblActualConversionRate.Font.FontFamily, lblActualConversionRate.Font.Size,
                                FontStyle.Regular);
                            lblActualConversionRate.Text = numSampleRate.Text;
                        }
                        else
                        {
                            lblActualConversionRate.Font = new System.Drawing.Font(
                                lblActualConversionRate.Font.FontFamily, lblActualConversionRate.Font.Size,
                                (FontStyle.Bold | FontStyle.Italic));
                            lblActualConversionRate.Text = lblNoRate.Text;
                        }
                    }
                    catch { }
                }
            }
            else
            {
                lblConversionRateLabel.Enabled = true;
                lblActualConversionRate.Enabled = true;
                if (m_params.IsArchMemberAvailable)
                {
                    tbClockFreq.Visible = true;
                    lblNoFreq.Visible = false;
                    m_clockValue = m_params.GetInternalFreq();
                    tbClockFreq.Text = m_clockValue.ToString();
                    double internalClockInKHz = CyClockReader.GetInternalClockInKHz(m_params.InstQuery.DesignQuery,
                        m_params.InstanceName);

                    if (internalClockInKHz > 0)
                    {
                        lblActualConversionRate.Font = new System.Drawing.Font(lblActualConversionRate.Font.FontFamily,
                            lblActualConversionRate.Font.Size, FontStyle.Regular);
                        lblActualConversionRate.Text = m_params.GetSampleRate(internalClockInKHz).ToString();
                    }
                    else
                    {
                        lblActualConversionRate.Font = new System.Drawing.Font(lblActualConversionRate.Font.FontFamily,
                            lblActualConversionRate.Font.Size, (FontStyle.Bold | FontStyle.Italic));
                        lblActualConversionRate.Text = lblNoRate.Text;
                    }
                }
                else
                {
                    tbClockFreq.Visible = false;
                    lblNoFreq.Visible = true;
                    lblActualConversionRate.Font = new System.Drawing.Font(lblActualConversionRate.Font.FontFamily,
                        lblActualConversionRate.Font.Size, (FontStyle.Bold | FontStyle.Italic));
                    lblActualConversionRate.Text = lblNoRate.Text;
                }
            }
            if (lblActualConversionRate.Text == lblNoRate.Text)
                lblActualConversionRate.Left = lblNoRate.Left;
            else
                lblActualConversionRate.Left = lblNoRate.Left + 3;
        }

        public void UpdateSampleRateData()
        {
            if (m_params.AdcClockSource == CyEAdcClockSrcType.External)
            {
                if (m_params.IsArchMemberAvailable)
                {
                    bool vis = m_params.m_externalClockInKHz >= 0;
                    numSampleRate.Visible = vis;
                    numSampleRate.Enabled = !vis;
                    lblNoRate.Visible = !vis;
                    uint extSampleRate = m_params.GetExternalSampleRate();
                    if (extSampleRate > 0)
                        numSampleRate.Text = extSampleRate.ToString();
                }
                else
                {
                    numSampleRate.Visible = false;
                    lblNoRate.Visible = true;
                }
            }
            else
            {
                numSampleRate.Visible = true;
                numSampleRate.Enabled = true;
                lblNoRate.Visible = false;
                numSampleRate.Value = m_params.AdcSampleRate;
            }
        }

        // Check what combination of Input Range and Reference is selected
        private void UpdateRefVoltageControl()
        {
            bool isInternalRef = (cbReference.Text.Contains(REF_EXTERNAL) == false);
            if (cbInputRange.Text.Contains(RANGE_VDDA) || cbInputRange.Text.Contains(RANGE_VDAC))
            {
                numRefVoltage.Enabled = true;
                Volts_label.Text = "Volts";
                if (cbInputRange.Text.Contains(RANGE_VDAC))
                {
                    if (isInternalRef)
                        Volts_label.Text = "Volts (Vdac)";
                }
                else if (cbInputRange.Text.Contains(RANGE_VDDA))
                {
                    if (isInternalRef)
                    {
                        Volts_label.Text = "Volts (Vdda)";
                        numRefVoltage.Enabled = false;

                        // Getting system Vdda and assigning it to voltage reference if Vdda range
                        string vnegVddaDiff = CyDictParser.GetDictValue(m_params.m_dnDict,
                            CyEAdcInputRangeType.Vneg_Vdda_Diff);
                        if (cbInputRange.SelectedItem.ToString() == vnegVddaDiff)
                        {
                            numRefVoltage.Text = m_params.m_systemVdda.ToString();
                        }
                        else
                        {
                            decimal dividedVdda = (decimal)m_params.m_systemVdda / 2;
                            numRefVoltage.Text = dividedVdda.ToString();
                            if (isInternalRef)
                                Volts_label.Text = "Volts (Vdda/2)";
                        }
                    }
                }
                else
                {
                    Volts_label.Text = "Volts";
                }
            }
            else
            {
                Volts_label.Text = "Volts";
                if (isInternalRef)
                {
                    numRefVoltage.Value = 1.024M;
                    numRefVoltage.Enabled = false;
                }
                else
                {
                    numRefVoltage.Enabled = true;
                }
            }
        }
        #endregion
    }
}
