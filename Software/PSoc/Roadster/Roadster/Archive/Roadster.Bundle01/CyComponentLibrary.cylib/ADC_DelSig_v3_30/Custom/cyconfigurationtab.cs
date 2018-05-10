/******************************************************************************
* Copyright 2008-2013, Cypress Semiconductor Corporation.  All rights reserved.
* You may use this file only in accordance with the license, terms, conditions, 
* disclaimers, and limitations in the end user license agreement accompanying 
* the software package with which this file was provided.
*******************************************************************************/


using CyDesigner.Extensions.Common;
using System;
using System.Drawing;
using System.Text.RegularExpressions;
using System.Windows.Forms;

namespace ADC_DelSig_v3_30
{
    public partial class CyConfigurationTab : CyTabControlWrapper
    {
        private const int VREF_DECIMAL_PLACES = 3;

        // Left alignment combo box options
        private string[] ALIGNMENT_LEFT_8_15_OPTIONS =
        {
            "16 bits (OVF Protected)",
            "16 bits (Not OVF Protected)"
        };
        private string[] ALIGNMENT_LEFT_16_OPTIONS = 
        {
            "24 bits (OVF Protected)",
            "16 bits (Not OVF Protected)"
        };
        private string[] ALIGNMENT_LEFT_17_20_OPTIONS =
        {
            "Bit-23 (OVF Protected)"
        };

        private byte m_configId;
        private bool m_vRefNumUpdate;

        #region CyTabControlWrapper Members
        public override string TabName
        {
            get
            {
                return m_params.GetConfigurationTabName(m_configId);
            }
        }
        #endregion

        public string TabDisplayName
        {
            get { return Resource.ConfigTabBaseDisplayName + m_configId.ToString(); }
        }

        #region Constructor(s)
        public CyConfigurationTab(CyParameters parameters, byte configId)
            : base(parameters)
        {
            InitializeComponent();

            m_configId = configId;

            #region Initialize UI
            // Initialize combobox ranges
            CyParameters.FillComboFromEnum(m_cbConvMode, typeof(CyEConversionMode));
            CyParameters.FillComboFromEnum(m_cbBufferGain, typeof(CyEBufferGain));
            CyParameters.FillComboFromEnum(m_cbBufferMode, typeof(CyEBufferMode));
            CyParameters.FillComboFromEnum(m_cbRef, typeof(CyEReference));

            for (byte i = CyParamRanges.MIN_RESOLUTION; i <= CyParamRanges.MAX_RESOLUTION; i++)
            {
                m_cbResolution.Items.Add(i);   
            }

            m_numRefValue.DecimalPlaces = VREF_DECIMAL_PLACES;

            // Set numericUpDown ranges
            m_numConvRate.Minimum = decimal.MinValue;
            m_numConvRate.Maximum = decimal.MaxValue;
            m_numRefValue.Minimum = decimal.MinValue;
            m_numRefValue.Maximum = decimal.MaxValue;

            // Assign event handlers
            m_tbComment.TextChanged += new EventHandler(m_tb_TextChanged);
            m_tbConfigName.TextChanged += new EventHandler(m_tb_TextChanged);

            m_cbConvMode.SelectedIndexChanged += new EventHandler(m_cb_SelectedIndexChanged);
            m_cbResolution.SelectedIndexChanged += new EventHandler(m_cb_SelectedIndexChanged);
            m_numConvRate.TextChanged += new EventHandler(m_num_TextChanged);

            m_cbInputRange.SelectedIndexChanged += new EventHandler(m_cb_SelectedIndexChanged);
            m_cbBufferGain.SelectedIndexChanged += new EventHandler(m_cb_SelectedIndexChanged);
            m_cbBufferMode.SelectedIndexChanged += new EventHandler(m_cb_SelectedIndexChanged);

            m_cbRef.SelectedIndexChanged += new EventHandler(m_cb_SelectedIndexChanged);
            m_numRefValue.TextChanged += new EventHandler(m_num_TextChanged);

            m_rbLeft.CheckedChanged += new EventHandler(m_rb_CheckedChanged);
            m_rbRight.CheckedChanged += new EventHandler(m_rb_CheckedChanged);
            m_cbLeftAlign.SelectedIndexChanged += new EventHandler(m_cb_SelectedIndexChanged);
            #endregion

            m_params.m_configTabs[m_configId - 1] = this;
        }
        #endregion

        #region Update UI
        public void UpdateUI()
        {
            m_tbComment.Text = m_params.GetComment(m_configId);
            m_tbConfigName.Text = m_params.GetConfigName(m_configId);

            CyParameters.SetComboValue(m_cbConvMode, m_params.GetConversionMode(m_configId));
            m_cbResolution.SelectedIndex = Math.Max(0,m_cbResolution.Items.IndexOf(m_params.GetResolution(m_configId)));

            UpdateInputRangeList();
            CyParameters.SetComboValue(m_cbBufferGain, m_params.GetBufferGain(m_configId));
            m_cbBufferGain.EnabledChanged += new EventHandler(m_cbBufferGain_EnabledChanged);
            CyParameters.SetComboValue(m_cbBufferMode, m_params.GetBufferMode(m_configId));

            UpdateReferenceComboBox();
            // m_numRefValue is initialized automatically when m_cbRef value is changed

            switch (m_params.GetAlignment(m_configId))
            {
                case CyEAlignment.Right:
                    m_rbRight.Checked = true;
                    break;
                case CyEAlignment.Left_OVF_Protected:
                case CyEAlignment.Left_Not_OVF_Protected:
                    m_rbLeft.Checked = true;
                    break;
            }
            
            UpdateClockRelatedFields(false);
            if (m_params.ClockSourceType == CyEClockSource.Internal)
            {
                m_numConvRate.Text = m_params.GetScanRate(m_configId).ToString();
            }

            UpdateLeftAlignmentComboBox();
            UpdateInputRangeGraph();
            DisplayInterruptMessage();
        }

        public void UpdateInputOptionsGroupBoxName()
        {
            m_grpInputMode.Text = string.Format(Resource.InputOptionsGroupboxTitleFormat,
                (m_params.InputModeType == CyEInputMode.Differential_Mode ? "Differential" : "Single ended"));
        }

        private void UpdateLeftAlignmentComboBox()
        {
            m_cbLeftAlign.Items.Clear();
            int resolution = m_params.GetResolution(m_configId);
            if (resolution <= CyParamRanges.ALIGN_RESOLUTION_RANGE_1)
            {
                m_cbLeftAlign.Items.AddRange(ALIGNMENT_LEFT_8_15_OPTIONS);
            }
            else if (resolution <= CyParamRanges.ALIGN_RESOLUTION_RANGE_2)
            {
                m_cbLeftAlign.Items.AddRange(ALIGNMENT_LEFT_16_OPTIONS);
            }
            else
            {
                m_cbLeftAlign.Items.AddRange(ALIGNMENT_LEFT_17_20_OPTIONS);
            }

            CyEAlignment alignment = m_params.GetAlignment(m_configId);
            if (alignment == CyEAlignment.Left_Not_OVF_Protected && m_cbLeftAlign.Items.Count > 1)
            {
                m_cbLeftAlign.SelectedIndex = (int)alignment - 1;
            }
            else
            {
                m_cbLeftAlign.SelectedIndex = 0;
            }
        }

        private void UpdateInputRangeGraph()
        {
            Bitmap image = null;

            switch (m_params.GetBufferMode(m_configId))
            {
                case CyEBufferMode.Bypass_Buffer:
                    image = Resource.BypassBuffer;
                    break;
                case CyEBufferMode.Level_Shift:
                    image = Resource.LevelShift;
                    break;
                case CyEBufferMode.Rail_to_Rail:
                    image = Resource.RailToRail;
                    break;
            }

            if (image != null)
            {
                m_pictInputRange.Image = image;
                m_pictInputRange.Location = new Point(
                    (m_grpInputRange.Width - m_pictInputRange.Width) / 2, m_pictInputRange.Location.Y);
            }
        }

        private void DisplayInterruptMessage()
        {
            int regularWidth = m_grpInputRange.Left + m_grpInputRange.Width / 3 - m_grpModes.Left;
            int extendedWidth = m_grpInputRange.Left + m_grpInputRange.Width - m_grpModes.Left + 1;
           
            if (m_params.GetConversionMode(m_configId) == CyEConversionMode.Single_Sample &&
                m_params.GetResolution(m_configId) > 16)
            {
                panelGlobalIntWarning.Visible = true;
                m_grpModes.Width = extendedWidth;
            }
            else
            {
                panelGlobalIntWarning.Visible = false;
                m_grpModes.Width = regularWidth;
            }
        }

        #region Updating "Input Range" ComboBox items
        public void UpdateInputRangeList()
        {
            const int VSSA_LAST_VALUE = 3;
            m_cbInputRange.Items.Clear();
            foreach (CyEInputRange value in Enum.GetValues(typeof(CyEInputRange)))
            {
                if (((int)value <= VSSA_LAST_VALUE && m_params.InputModeType == CyEInputMode.Differential_Mode) ||
                    ((int)value > VSSA_LAST_VALUE && m_params.InputModeType == CyEInputMode.Single_Mode))
                    continue;

                m_cbInputRange.Items.Add(value);
            }
            if (m_cbInputRange.Items.Contains(m_params.GetInputRange(m_configId)))
            {
                m_cbInputRange.SelectedItem = m_params.GetInputRange(m_configId);
            }
            else
            {
                m_cbInputRange.SelectedIndex = 0;
            }
        }

        private string GetInputRangeItemString(CyEInputRange value)
        {
            string descr = CyParameters.GetDescription(value);

            if (value != CyEInputRange.Vssa_to_Vdda)
            {
                string format = string.Empty;

                if (value == CyEInputRange.Vssa_to_Vref || value == CyEInputRange.Vssa_to_2Vref ||
                    value == CyEInputRange.Vssa_to_6Vref)
                {
                    format = Resource.SingleEndedInputRangeDescriptionFormat;
                }
                else
                {
                    format = Resource.DifferentialInputRangeDescriptionFormat;
                }

                descr = string.Format(format, m_params.GetVrefValue(m_configId) * GetInputRangeValueMultiplier(value),
                    descr);
            }

            return descr;
        }

        private double GetInputRangeValueMultiplier(CyEInputRange value)
        {
            double result = 1.0;

            switch (value)
            {
                case CyEInputRange.Vneg_2Vref_Diff:
                case CyEInputRange.Vssa_to_2Vref:
                    result = 2.0;
                    break;
                case CyEInputRange.Vneg_6Vref_Diff:
                case CyEInputRange.Vssa_to_6Vref:
                    result = 6.0;
                    break;
                case CyEInputRange.Vneg_Vref16_Diff:
                    result = 1.0 / 16.0;
                    break;
                case CyEInputRange.Vneg_Vref2_Diff:
                    result = 1.0 / 2.0;
                    break;
                case CyEInputRange.Vneg_Vref4_Diff:
                    result = 1.0 / 4.0;
                    break;
                case CyEInputRange.Vneg_Vref8_Diff:
                    result = 1.0 / 8.0;
                    break;
            }

            return result;
        }

        private void m_cbInputRange_Format(object sender, ListControlConvertEventArgs e)
        {
            e.Value = GetInputRangeItemString((CyEInputRange)e.Value);
        }
        #endregion

        #region Update "Reference" ComboBox items

        private void UpdateReferenceComboBox()
        {
            CyEInputRange inputRange = m_params.GetInputRange(m_configId);
            if (inputRange == CyEInputRange.Vssa_to_Vdda)
            {
                m_cbRef.Items.Clear();
                // Ranges [2.7; 3.75) and [3.75; 5.2)
                if (m_params.VDDA < CyParamRanges.MAX_VDDA3_VALUE)
                {
                    m_cbRef.Items.Add(CyParameters.GetDescription(CyEReference.Internal_Vdda_3_Ref));
                    m_cbRef.Items.Add(CyParameters.GetDescription(CyEReference.Internal_Vdda_3_Ref_Bypassed_On_P03));
                    m_cbRef.Items.Add(CyParameters.GetDescription(CyEReference.Internal_Vdda_3_Ref_Bypassed_On_P32));
                }
                else
                {
                    m_cbRef.Items.Add(CyParameters.GetDescription(CyEReference.Internal_Vdda_4_Ref));
                    m_cbRef.Items.Add(CyParameters.GetDescription(CyEReference.Internal_Vdda_4_Ref_Bypassed_On_P03));
                    m_cbRef.Items.Add(CyParameters.GetDescription(CyEReference.Internal_Vdda_4_Ref_Bypassed_On_P32));
                }  
            }
            else
            {
                CyParameters.FillComboFromEnum(m_cbRef, typeof(CyEReference));
            }
            CyParameters.SetComboValue(m_cbRef, m_params.GetReference(m_configId));
            if (m_cbRef.SelectedItem == null)
                m_cbRef.SelectedIndex = 0;
        }
        #endregion
        #endregion

        #region Event handlers
        void m_tb_TextChanged(object sender, EventArgs e)
        {
            TextBox tb = sender as TextBox;
           
            if (tb == m_tbComment)
            {
                m_params.SetComment(m_configId, tb.Text);
            }
            else if (tb == m_tbConfigName)
            {
                m_params.SetConfigName(m_configId, tb.Text);
                UpdateConfigName();

                // Check if the name is valid C language name
                Regex reg = new Regex(@"[^_a-zA-Z0-9]");
                MatchCollection matches = reg.Matches(tb.Text);
                if (matches.Count > 0 || !IsUniqueConfigName(tb.Text))
                {
                    m_errorProvider.SetError(tb, Resource.ConfigNameErrorDescription);
                }
                else
                {
                    m_errorProvider.SetError(tb, string.Empty);
                }
            }
        }

        void m_cb_SelectedIndexChanged(object sender, EventArgs e)
        {
            ComboBox cb = sender as ComboBox;

            if (cb == m_cbConvMode)
            {
                m_params.SetConversionMode(m_configId, CyParameters.GetEnum<CyEConversionMode>(cb.Text));
                UpdateClockRelatedFields(true);
                DisplayInterruptMessage();
            }
            else if (cb == m_cbInputRange)
            {
                if (cb.SelectedItem == null)
                    return;

                CyEInputRange value = (CyEInputRange)cb.SelectedItem;
                m_params.SetInputRange(m_configId, value);

                // Update reference value
                UpdateReferenceComboBox();
                UpdateClockRelatedFields(true);
            }
            else if (cb == m_cbBufferGain)
            {
                m_params.SetBufferGain(m_configId, CyParameters.GetEnum<CyEBufferGain>(cb.Text));
                UpdateClockRelatedFields(true);
            }
            else if (cb == m_cbBufferMode)
            {
                CyEBufferMode mode = CyParameters.GetEnum<CyEBufferMode>(cb.Text);
                m_params.SetBufferMode(m_configId, mode);
                UpdateInputRangeGraph();

                // Update Buffer Gain combobox state
                m_cbBufferGain.Enabled = (mode != CyEBufferMode.Bypass_Buffer);
            }
            else if (cb == m_cbRef)
            {
                if (cb.SelectedItem == null)
                    return;

                CyEReference refValue = CyParameters.GetEnum<CyEReference>(cb.Text);
                m_params.SetReference(m_configId, refValue);

                // Update reference voltage control
                if (m_vRefNumUpdate == false)
                {
                    double vRef;
                    CyCustErr err = m_params.CalcVddaVRef(out vRef, m_configId);
                    m_numRefValue.Text = vRef.ToString();
                    m_numRefValue.Enabled = (refValue == CyEReference.Ext_Ref_On_P03) ||
                                            (refValue == CyEReference.Ext_Ref_On_P32);
                    if (err != CyCustErr.OK)
                    {
                        m_errorProvider.SetError(m_numRefValue, err.Message);
                    }
                }
            }
            else if (sender == m_cbResolution)
            {
                byte value = Convert.ToByte(m_cbResolution.SelectedItem);
                m_params.SetResolution(m_configId, value);
                UpdateLeftAlignmentComboBox();
                UpdateClockRelatedFields(true);
                DisplayInterruptMessage();
            }
            else if (cb == m_cbLeftAlign)
            {
                SetAlignment();
            }
        }

        void m_cbBufferGain_EnabledChanged(object sender, EventArgs e)
        {
            if (m_cbBufferGain.Enabled && m_cbBufferGain.Tag != null)
            {
                m_cbBufferGain.SelectedItem = m_cbBufferGain.Tag;
            }
            else
            {
                m_cbBufferGain.Tag = m_cbBufferGain.SelectedItem;
                m_cbBufferGain.SelectedItem = CyParameters.GetDescription(CyEBufferGain.Gain_1X);
            }
        }

        void m_num_TextChanged(object sender, EventArgs e)
        {
            NumericUpDown num = sender as NumericUpDown;

            if (sender == m_numConvRate)
            {
                UInt32 value;
                bool parsed = UInt32.TryParse(num.Text, out value);

                if (parsed)
                {
                    m_params.SetScanRate(m_configId, value);
                    m_errorProvider.SetError(num, string.Empty);
                    UpdateClockRelatedFields(false);
                }
            }
            else if (sender == m_numRefValue)
            {
                m_vRefNumUpdate = true;

                double value;
                bool parsed = double.TryParse(num.Text, out value);

                if (parsed)
                {
                    m_params.SetVrefValue(m_configId, value);
                }

                if (parsed && value >= CyParamRanges.MIN_VREF_VALUE && value <= CyParamRanges.MAX_VREF_VALUE)
                {
                    m_errorProvider.SetError(num, string.Empty);
                    UpdateInputRangeList();
                }
                else
                {
                    m_errorProvider.SetError(num, Resource.ErrorVrefRange);
                }

                m_vRefNumUpdate = false;
            }
        }

        void m_rb_CheckedChanged(object sender, EventArgs e)
        {
            RadioButton rb = sender as RadioButton;

            if (rb == m_rbLeft || rb == m_rbRight)
            {
                SetAlignment();
                m_cbLeftAlign.Enabled = m_rbLeft.Checked;
            }
        }
        #endregion

        #region Auxiliary operations
        public void UpdateConfigName()
        {
            m_lblFullConfigName.Text = m_params.m_inst.InstanceName + "_" + m_params.GetConfigName(m_configId);
        }

        private bool IsUniqueConfigName(string configName)
        {
            if (m_params != null)
            {
                for (byte i = CyParamRanges.NUM_MIN_CONFIG; i <= CyParamRanges.NUM_MAX_CONFIG; i++)
                {
                    if (i != m_configId && configName == m_params.GetConfigName(i))
                    {
                        return false;
                    }
                }
            }

            return true;
        }

        private void SetAlignment()
        {
            CyEAlignment alignmentValue = CyEAlignment.Right;
            if (m_rbLeft.Checked)
            {
                if (m_cbLeftAlign.SelectedIndex == 0)
                    alignmentValue = CyEAlignment.Left_OVF_Protected;
                else
                    alignmentValue = CyEAlignment.Left_Not_OVF_Protected;
            }
            m_params.SetAlignment(m_configId, alignmentValue);

            uint decCoherValue = CyParameters.GetCoherency(m_params.GetResolution(m_configId), alignmentValue);
            string coherencyStr = (decCoherValue == Cyrc.DEC_SAMP_KEY_HIGH) ? "HIGH" : 
                                  (decCoherValue == Cyrc.DEC_SAMP_KEY_MID) ? "MID" : "LOW";
            labelDecCoher.Text = String.Format("Coherency = {0}", coherencyStr);            
        }
        #endregion

        #region Clock frequency related functions 
        // Check the current ADC settings for clock frequencies that are beyond the clock specifications.
        private bool UpdateClockRelatedFields(bool adjustSampleRate)
        {
            uint resolution = m_params.GetResolution(m_configId);
            CyEConversionMode conversionMode = m_params.GetConversionMode(m_configId); 
            uint convRate = m_params.GetScanRate(m_configId);

            uint calcSampleRate = 0;
            uint minRate, maxRate;
            float frequency;
            double maxFreq;
            double minFreq;
            bool frequencyOutOfRange = false;
            bool retVal = true;

            m_params.GetMinMaxClockFreqSampleRate(m_configId, out minFreq, out maxFreq, out minRate, out maxRate);

            // Get clock frequency
            if (m_params.ClockSourceType == CyEClockSource.Internal)
            {
                frequency = CyCustomizer.SetClock(resolution, convRate, conversionMode);

                if (adjustSampleRate)
                {
                    if (frequency < minFreq)
                    {
                        frequencyOutOfRange = true;
                        frequency = (float)minFreq;
                        calcSampleRate = CyCustomizer.GetSampleRate(resolution, frequency, conversionMode, 
                            false);
                    }
                    else if (frequency > maxFreq)
                    {
                        frequencyOutOfRange = true;
                        frequency = (float)maxFreq;
                        calcSampleRate = CyCustomizer.GetSampleRate(resolution, frequency, conversionMode,
                            true);
                    }
                }
            }
            else
            {
                frequency = (float)m_params.GetExternalClockInHz();
                if (CyParameters.IsFrequencyKnown(frequency))
                {
                    bool closerToMaxFreq = (Math.Abs(maxFreq - frequency)) < (Math.Abs(minFreq - frequency));
                    calcSampleRate = CyCustomizer.GetSampleRate(resolution, frequency, conversionMode, closerToMaxFreq);
                }
            }

            if (CyParameters.IsFrequencyKnown(frequency) && ((frequency > maxFreq) || (frequency < minFreq)))
            {
                if (m_params.ClockSourceType == CyEClockSource.Internal)
                    m_errorProvider.SetError(m_numConvRate, Resource.SampleRateOutOfRange);
                else
                    errProviderExtClock.SetError(m_tbClockFreq, String.Format(Resource.DRCErrorExternalClockRange,
                        CyParameters.FormatFrequencyKHz(minFreq), CyParameters.FormatFrequencyKHz(maxFreq)));
                retVal = false;
            }
            else
            {
                errProviderExtClock.SetError(m_tbClockFreq, String.Empty);
                m_errorProvider.SetError(m_numConvRate, String.Empty);
                retVal = true;
            }

            bool isFrequencyKnown = CyParameters.IsFrequencyKnown(frequency);
            // Fill m_tbClockFreq
            if (isFrequencyKnown)
            {
                m_tbClockFreq.Text = CyParameters.FormatFrequencyKHz(frequency);

                // Fill m_numConvRate if ClockSourceType = External
                if ((m_params.ClockSourceType == CyEClockSource.External) || frequencyOutOfRange)
                {
                    m_numConvRate.Value = calcSampleRate;
                }
            }
            m_numConvRate.Visible = isFrequencyKnown;
            m_tbClockFreq.Visible = isFrequencyKnown;
            m_lblRateRange.Visible = isFrequencyKnown;
            m_lblUnknownRate.Visible = !isFrequencyKnown;
            m_lblUnknownFreq.Visible = !isFrequencyKnown;
           
            // Fill m_lblRateRange
            m_lblRateRange.Text = String.Format(Resource.SampleRateRangeLabelText, minRate, maxRate);

            // Actual sample rate
            // Get MASTER_CLOCK value
            double masterClockFrequency = m_params.GetMasterClockInHz();
            bool isMasterClockFrequencyKnown = CyParameters.IsFrequencyKnown(masterClockFrequency);
            if (isFrequencyKnown && isMasterClockFrequencyKnown)
            {
                UInt16 clockDivider;
                CyCustErr dividerErr = CyParameters.GetClockDivider((float)masterClockFrequency, frequency,
                                                                    (float)minFreq, (float)maxFreq, out clockDivider);
                double actualFrequency = Math.Round(masterClockFrequency / clockDivider);
                bool closerToMaxActFreq = (Math.Abs(maxFreq - actualFrequency)) < (Math.Abs(minFreq - actualFrequency));
                uint actSampleRate = CyCustomizer.GetSampleRate(resolution, (float)actualFrequency, conversionMode,
                    closerToMaxActFreq);
                m_tbActualRate.Text = actSampleRate.ToString();
                m_tbActualRate.Visible = true;
                m_lblUnknownActRate.Visible = false;

                errProviderExtClock.SetError(m_tbActualRate,
                    dividerErr == CyCustErr.OK ? String.Empty : dividerErr.Message);
            }
            else
            {
                m_tbActualRate.Visible = false;
                m_lblUnknownActRate.Visible = true;
            }
            

            return retVal;
        }

        private bool CheckFrequencyRange(ref float frequency)
        {
            bool outOfRange = false;
            if (frequency < CyParamRanges.MIN_CLOCK_FREQ)
            {
                frequency = CyParamRanges.MIN_CLOCK_FREQ;
                outOfRange = true;
            }
            if (frequency > CyParamRanges.MAX_8_15_CLOCK_FREQ && m_params.GetResolution(m_configId) <= 15)
            {
                frequency = CyParamRanges.MAX_8_15_CLOCK_FREQ;
                outOfRange = true; 
            }
            if (frequency > CyParamRanges.MAX_16_20_CLOCK_FREQ && m_params.GetResolution(m_configId) > 15)
            {
                frequency = CyParamRanges.MAX_16_20_CLOCK_FREQ;
                outOfRange = true;
            }
            return outOfRange;
        }

        public void UpdateClockSourceDependencies()
        {
            m_numConvRate.Enabled = (m_params.ClockSourceType == CyEClockSource.Internal);
            if (m_params.ClockSourceType == CyEClockSource.Internal)
            {
                m_numConvRate.Minimum = CyParamRanges.MIN_CONV_RATE;
                m_numConvRate.Maximum = CyParamRanges.MAX_CONV_RATE;
            }
            else
            {
                m_numConvRate.Minimum = 0;
                m_numConvRate.Maximum = decimal.MaxValue;
            }
            UpdateClockRelatedFields(true);
        }
        #endregion Clock frequency related functions
    }
}
