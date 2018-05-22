/*******************************************************************************
* Copyright 2011-2015, Cypress Semiconductor Corporation.  All rights reserved.
* You may use this file only in accordance with the license, terms, conditions, 
* disclaimers, and limitations in the end user license agreement accompanying 
* the software package with which this file was provided.
********************************************************************************/

using CyDesigner.Extensions.Gde;
using System;

namespace ADC_SAR_SEQ_P4_v2_50.Tabs
{
    public partial class CyGeneralTab : CyTabControlWrapper
    {
        #region CyTabControlWrapper Members
        public override string TabName
        {
            get
            {
                return "General";
            }
        }
        #endregion

        #region Constructor(s)
        public CyGeneralTab(CyParameters param) 
            : base(param)
        {
            // Initialize parameters objects
            m_params.m_generalTab = this;

            InitializeComponent();

            #region Initialize clock frequency numeric
            m_numClkFreq.Increment = CyParameters.FREQ_KHZ_INCREMENT;
            #endregion

            #region Add ranges for comboboxes
            m_cbVrefSel.Items.AddRange(m_params.GetEnumDescriptions(CyParamNames.VREF_SELECT_TYPE));
            m_cbSingleEndNegInput.Items.AddRange(m_params.GetEnumDescriptions(
                CyParamNames.SINGLE_ENDED_NEGATIVE_INPUT));
            m_cbDiffResultFormat.Items.AddRange(m_params.GetEnumDescriptions(CyParamNames.DIFFERENTIAL_RESULT_FORMAT));
            m_cbSingleEndResultFormat.Items.AddRange(m_params.GetEnumDescriptions(
                CyParamNames.SINGLE_ENDED_RESULT_FORMAT));
            m_cbDataFormatJustify.Items.AddRange(m_params.GetEnumDescriptions(CyParamNames.DATA_FORMAT_JUSTIFICATION));
            m_cbSampleAveraged.Items.AddRange(m_params.GetEnumDescriptions(CyParamNames.SAMPLES_AVERAGED));
            m_cbAverageMode.Items.AddRange(m_params.GetEnumDescriptions(CyParamNames.AVERAGING_MODE));
            m_cbAlterResolution.Items.AddRange(m_params.GetEnumDescriptions(CyParamNames.ALTERNATE_RESOLUTION));
            m_cbCompareMode.Items.AddRange(m_params.GetEnumDescriptions(CyParamNames.COMPARE_MODE));
            #endregion

            #region Add event handlers
            m_numScanRate.TextChanged += new EventHandler(m_numUpDown_TextChanged);
            m_numClkFreq.TextChanged += new EventHandler(m_numUpDown_TextChanged);
            m_numVrefVal.TextChanged += new EventHandler(m_numUpDown_TextChanged);
            m_numLowLimit.TextChanged += new EventHandler(m_numUpDown_TextChanged);
            m_numHighLimit.TextChanged += new EventHandler(m_numUpDown_TextChanged);
            #endregion

            #region Initialize all NumericUpDown ranges
            m_numScanRate.Minimum = 0;
            m_numScanRate.Maximum = decimal.MaxValue;

            m_numClkFreq.Minimum = 0;
            m_numClkFreq.Maximum = decimal.MaxValue;

            m_numLowLimit.Minimum = 0;
            m_numLowLimit.Maximum = decimal.MaxValue;

            m_numHighLimit.Minimum = 0;
            m_numHighLimit.Maximum = decimal.MaxValue;

            m_numVrefVal.Minimum = 0;
            m_numVrefVal.Maximum = decimal.MaxValue;
            #endregion

            Load += delegate(object sender, EventArgs e)
            {
                UpdateClockData(m_params.InstQuery, m_params.TermQuery);
            };

            m_rbExternal.Visible = !m_params.InstQuery.IsInSystemBuilder;
        }
        #endregion

        #region Update UI
        public void UpdateUI()
        {
            if (m_params == null) return;

            #region Timimg groupbox
            if (m_params.AdjustType == CyEAdjust.ScanRate)
            {
                m_rbSampleRate.Checked = true;
            }
            else
            {
                m_rbClkFreq.Checked = true;
            }

            m_numClkFreq.Text = m_params.ClockFrequencyKHz.ToString();
            m_numScanRate.Text = m_params.GetSampleRate(m_params.ClockFrequency).ToString();
            UpdateClockData(m_params.InstQuery, m_params.TermQuery);
            #endregion

            #region Clock source groupbox
            if (m_params.ClockSourceType == CyESarAdcClockSrc.Internal)
            {
                m_rbInternal.Checked = true;
            }
            else
            {
                m_rbExternal.Checked = true;
            }
            #endregion

            #region Sample mode groupbox
            if (m_params.SampleModeType == CyESampleMode.FreeRunning)
            {
                m_rbFreeRun.Checked = true;
            }
            else
            {
                m_rbHardwareSOC.Checked = true;
            }
            #endregion

            #region Input range groupbox
            m_cbVrefSel.SelectedItem = m_params.GetValueDescription(CyParamNames.VREF_SELECT_TYPE,
                m_params.VrefSelect);
            m_cbSingleEndNegInput.SelectedItem = m_params.GetValueDescription(CyParamNames.SINGLE_ENDED_NEGATIVE_INPUT,
                m_params.SingleEndedNegativeInput);
            UpdateVoltageRefControl();
            UpdateModeRanges();
            #endregion

            #region Result data format groupbox
            m_cbDiffResultFormat.SelectedItem = m_params.GetValueDescription(CyParamNames.DIFFERENTIAL_RESULT_FORMAT,
                m_params.DifferentialResultFormat);
            m_cbSingleEndResultFormat.SelectedItem = m_params.GetValueDescription(
                CyParamNames.SINGLE_ENDED_RESULT_FORMAT, m_params.SingleEndedResultFormat);
            m_cbDataFormatJustify.SelectedItem = m_params.GetValueDescription(CyParamNames.DATA_FORMAT_JUSTIFICATION,
                m_params.DataFormatJustification);
            m_cbSampleAveraged.SelectedItem = m_params.GetValueDescription(CyParamNames.SAMPLES_AVERAGED,
                m_params.SamplesAveraged);
            m_cbAlterResolution.SelectedItem = m_params.GetValueDescription(CyParamNames.ALTERNATE_RESOLUTION,
                m_params.AlternateResolution);
            m_cbAverageMode.SelectedItem = m_params.GetValueDescription(CyParamNames.AVERAGING_MODE,
                m_params.AveragingMode);
            UpdateResultFormat();
            #endregion

            #region Interrupt limits groupbox
            m_numLowLimit.Text = m_params.LowLimit.ToString("X");
            m_numHighLimit.Text = m_params.HighLimit.ToString("X");
            m_cbCompareMode.SelectedItem = m_params.GetValueDescription(CyParamNames.COMPARE_MODE,
                m_params.CompareMode);
            #endregion
        }

        public void UpdateTimimgParams()
        {
            if (m_params.ClockSourceType == CyESarAdcClockSrc.External || m_params.AdjustType == CyEAdjust.ClockFreq)
            {
                m_numScanRate.Text = m_params.GetSampleRate(m_params.ClockFrequency).ToString();
            }
            else
            {
                try
                {
                    m_numClkFreq.Text =
                        (UInt32.Parse(m_numScanRate.Text) * m_params.ClocksPerSample / 1000.0).ToString();
                    UpdateSPSClockFrequencyRanges();
                }
                catch { }
            }
            UpdateTimingControlsVisibility();
        }

        public void UpdateModeRanges()
        {
            // Differential mode range
            m_labelDiffModeRangeValue.Text = "Vn +/- " + GetVoltageString();

            // Single ended mode range
            if (m_params.SingleEndedNegativeInput == CyESingleEndedNegativeInput.Vss)
            {
                m_labelSingleEndModeRangeValue.Text = string.Format("0.0 to Vref ({0} V)",
                    m_params.ReferenceVoltageValue);
            }
            else
            {
                if (m_params.VrefSelect == CyEVRefSelect.VDDA)
                {
                    m_labelSingleEndModeRangeValue.Text = GetVoltageString() + " to 0.0";
                }
                else
                {
                    m_labelSingleEndModeRangeValue.Text = "0.0 to 2*Vref";
                    if (m_params.VrefSelect == CyEVRefSelect.VDDA_2 ||
                        m_params.VrefSelect == CyEVRefSelect.VDDA_2Bypassed)
                    {
                        double vrefValue = m_params.VDDA;
                        if (m_params.VrefSelect == CyEVRefSelect.VDDA)
                        {
                            vrefValue *= 2;
                        }
                        m_labelSingleEndModeRangeValue.Text += string.Format(" ({0} V)", vrefValue);
                    }
                    else if (m_params.VrefSelect == CyEVRefSelect.Internal1024 ||
                        m_params.VrefSelect == CyEVRefSelect.Internal1024Bypassed)
                    {
                        m_labelSingleEndModeRangeValue.Text += string.Format(" ({0} V)",
                            2 * CyParameters.DEFAULT_INTERNAL_VREF);
                    }
                }
            }
        }
        
        private void UpdateTimingControlsVisibility()
        {
            if (m_params.ClockSourceType == CyESarAdcClockSrc.External)
            {
                double clkFreq = CyClock.GetClockFrequencyHz(m_params.TermQuery, false, CyClock.INTERNAL_CLOCK_OR_GATE_NAME);

                m_numScanRate.Enabled = false;
                m_rbSampleRate.Enabled = false;
                m_numClkFreq.Enabled = false;
                m_rbClkFreq.Enabled = false;
                m_lblActualSRText.Enabled = false;
                m_lblActualCFText.Enabled = false;             
                m_lblUnknownActualRate.Enabled = false;
                m_lblUnknownActualFrequency.Enabled = false;   
                m_lblActualSampleRate.Enabled = false;
                m_lblActualClockFrequency.Enabled = false;     
                
                m_lblFrequencyRange.Visible = false;           
                m_lblSPSRange.Visible = false;                
                m_numScanRate.Visible = CyClock.IsFrequencyKnown(clkFreq);
                m_numClkFreq.Visible = CyClock.IsFrequencyKnown(clkFreq);
                m_lblActualSampleRate.Visible = CyClock.IsFrequencyKnown(clkFreq);
                m_lblActualClockFrequency.Visible = CyClock.IsFrequencyKnown(clkFreq);  
                m_lblUnknownRate.Visible = !CyClock.IsFrequencyKnown(clkFreq);
                m_lblUnknownFreq.Visible = !CyClock.IsFrequencyKnown(clkFreq);
                m_lblUnknownActualRate.Visible = !CyClock.IsFrequencyKnown(clkFreq);
                m_lblUnknownActualFrequency.Visible = !CyClock.IsFrequencyKnown(clkFreq); 
            }
            else
            {
                double clkFreq = CyClock.GetClockFrequencyHz(m_params.TermQuery, true, CyClock.INTERNAL_CLOCK_OR_GATE_NAME);
                
                m_numScanRate.Enabled = m_params.AdjustType == CyEAdjust.ScanRate;
                m_rbSampleRate.Enabled = true;
                m_numClkFreq.Enabled = m_params.AdjustType == CyEAdjust.ClockFreq;
                m_rbClkFreq.Enabled = true;
                m_lblActualSRText.Enabled = true;
                m_lblActualCFText.Enabled = true;           
                m_lblUnknownActualRate.Enabled = true;
                m_lblUnknownActualFrequency.Enabled = true; 
                m_lblActualSampleRate.Enabled = true;
                m_lblActualClockFrequency.Enabled = true;   

                m_lblFrequencyRange.Visible = true;         
                m_lblSPSRange.Visible = true;                
                m_numScanRate.Visible = true;
                m_numClkFreq.Visible = true;
                m_lblActualSampleRate.Visible = true;
                m_lblActualClockFrequency.Visible = true;  
                m_lblUnknownRate.Visible = false;
                m_lblUnknownFreq.Visible = false;

                m_lblUnknownActualRate.Visible = !CyClock.IsFrequencyKnown(clkFreq);
                m_lblUnknownActualFrequency.Visible = !CyClock.IsFrequencyKnown(clkFreq); 
            }
        }

        private void UpdateResultFormat()
        {
            if ((m_params.SingleEndedNegativeInput == CyESingleEndedNegativeInput.Vss) ||
                (m_params.SingleEndedNegativeInput == CyESingleEndedNegativeInput.Other))
            {
                m_cbSingleEndResultFormat.SelectedItem = m_params.GetValueDescription(
                    CyParamNames.SINGLE_ENDED_RESULT_FORMAT, CyEResultFormat.FSigned);
                m_cbSingleEndResultFormat.Enabled = false;
            }
            else
            {
                m_cbSingleEndResultFormat.Enabled = true;
                m_cbSingleEndResultFormat.SelectedItem = m_params.GetValueDescription(
                    CyParamNames.SINGLE_ENDED_RESULT_FORMAT, m_params.SingleEndedResultFormat);
            }
        }

        private string GetVoltageString()
        {
            string voltageString;
            double voltage = m_params.ReferenceVoltageValue;

            switch (m_params.VrefSelect)
            {
                case CyEVRefSelect.Internal1024:
                case CyEVRefSelect.Internal1024Bypassed:
                    voltageString = string.Format("{0} V", voltage);
                    break;
                case CyEVRefSelect.VDDA_2:
                case CyEVRefSelect.VDDA_2Bypassed:
                    voltageString = string.Format("Vdda/2 ({0} V)", voltage);
                    break;
                case CyEVRefSelect.InternalVref:
                case CyEVRefSelect.InternalVrefBypassed:
                    voltageString = "Vref";
                    break;
                case CyEVRefSelect.VDDA:
                    voltageString = string.Format("Vdda ({0} V)", voltage);
                    break;
                default:
                    voltageString = string.Format("{0} V", voltage);
                    break;
            }
            return voltageString;
        }

        private void UpdateVoltageRefControl()
        {
            m_numVrefVal.Enabled = (m_params.VrefSelect == CyEVRefSelect.ExternalVref);
            m_numVrefVal.Text = m_params.ReferenceVoltageValue.ToString();
        }

        private void UpdateSPSClockFrequencyRanges()
        {
            double maxFrequencyHz = m_params.GetMaxFrequencyHz();
            double minFrequencyHz = CyParamRanges.MIN_CLOCK_FREQ_HZ;
            
            uint maxSPS = m_params.GetSampleRate(maxFrequencyHz);
            uint minSPS = m_params.GetSampleRate(minFrequencyHz);

            if (minSPS * m_params.ClocksPerSample < minFrequencyHz)
                minSPS++;
            if (maxSPS * m_params.ClocksPerSample > maxFrequencyHz)
                maxSPS--;
            
            m_lblFrequencyRange.Text = string.Format("[{0:0} - {1:0}] kHz", minFrequencyHz / 1000, maxFrequencyHz / 1000);
            m_lblSPSRange.Text = string.Format("[{0:0} - {1:0}] SPS", minSPS, maxSPS);
        }
        #endregion

        #region Event Handlers
        private void m_numUpDown_TextChanged(object sender, EventArgs e)
        {
            if (m_params.GlobalEditMode)
            {
                if (sender == m_numLowLimit || sender == m_numHighLimit)
                {
                    UInt16 low;
                    UInt16 high;
                    
                    try
                    {
                        low = Convert.ToUInt16(m_numLowLimit.Text, 16);
                        if (sender == m_numLowLimit)
                        {
                            m_params.LowLimit = low;
                        }
                        m_errorProvider.SetError(m_numLowLimit, string.Empty);
                    }
                    catch (Exception)
                    {
                        m_errorProvider.SetError(m_numLowLimit, String.Format(Resources.InterruptValueError,
                            CyParamRanges.COMP_LIMIT_MIN_VALUE, CyParamRanges.COMP_LIMIT_MAX_VALUE.ToString("X")));
                    }

                    try
                    {
                        high = Convert.ToUInt16(m_numHighLimit.Text, 16);
                        if (sender == m_numHighLimit)
                        {
                            m_params.HighLimit = high;
                        }
                        m_errorProvider.SetError(m_numHighLimit, string.Empty);
                    }
                    catch (Exception)
                    {
                        m_errorProvider.SetError(m_numHighLimit, String.Format(Resources.InterruptValueError,
                            CyParamRanges.COMP_LIMIT_MIN_VALUE, CyParamRanges.COMP_LIMIT_MAX_VALUE.ToString("X")));
                    }
                }
                else if (sender == m_numScanRate) // Scan rate
                {
                    UInt32 value;
                    bool parseSuccess = UInt32.TryParse(m_numScanRate.Text, out value);

                    if (parseSuccess && m_params.ClockSourceType == CyESarAdcClockSrc.Internal &&
                        m_params.AdjustType == CyEAdjust.ScanRate)
                    {
                        m_numClkFreq.Text = (value * m_params.ClocksPerSample / 1000.0).ToString();
                    }
                }
                else if (sender == m_numClkFreq) // Clock frequency
                {
                    double value;
                    bool parseSuccess = double.TryParse(m_numClkFreq.Text, out value);

                    m_errorProvider.SetError(m_lblActualClockFrequency, string.Empty);         
                    
                    if (parseSuccess)
                    {
                        m_params.ClockFrequencyKHz = value;

                        m_numScanRate.Text = m_params.GetSampleRate(m_params.ClockFrequency).ToString();
                        if (m_params.m_channelsTab != null)
                        {
                            m_params.m_channelsTab.UpdateAcqTimeValues();
                            AcquisitionTimesAdjustment();
                        }
                    }

                    if (parseSuccess == false)
                    {
                        m_errorProvider.SetError(m_numClkFreq,
                                                m_params.GetClockFrequencyError(0));
                    }
                    else
                    {
                        m_errorProvider.SetError(m_numClkFreq,
                                                 m_params.GetClockFrequencyError(m_params.ClockFrequency));
                    }
                }
                else if (sender == m_numVrefVal) // Vref value
                {
                    double value;
                    bool parseSuccess = double.TryParse(m_numVrefVal.Text, out value);

                    if (parseSuccess && (m_params.VrefSelect == CyEVRefSelect.ExternalVref))
                    {
                        m_params.VrefValue = value;
                    }

                    m_errorProvider.SetError(m_numVrefVal, m_params.GetRefVoltageValueError());
                    UpdateModeRanges();
                }
            }
        }

        private void cb_SelectedIndexChanged(object sender, EventArgs e)
        {            
            if (sender == m_cbDiffResultFormat && m_params.GlobalEditMode)
            {
                m_params.DifferentialResultFormat = m_params.GetEnumValue<CyEResultFormat>(
                    CyParamNames.DIFFERENTIAL_RESULT_FORMAT, m_cbDiffResultFormat.Text);
            }
            else if (sender == m_cbSingleEndResultFormat && m_params.GlobalEditMode)
            {
                m_params.SingleEndedResultFormat = m_params.GetEnumValue<CyEResultFormat>(
                    CyParamNames.SINGLE_ENDED_RESULT_FORMAT, m_cbSingleEndResultFormat.Text);
            }
            else if (sender == m_cbDataFormatJustify && m_params.GlobalEditMode)
            {
                m_params.DataFormatJustification = m_params.GetEnumValue<CyEFormatJustify>(
                    CyParamNames.DATA_FORMAT_JUSTIFICATION, m_cbDataFormatJustify.Text);

                m_params.m_channelsTab.UpdateAvgLeftDataErrors();
            }
            else if (sender == m_cbSampleAveraged)
            {
                if (m_params.GlobalEditMode)
                {
                    m_params.SamplesAveraged = m_params.GetEnumValue<CyESamplesAveraged>(
                        CyParamNames.SAMPLES_AVERAGED, m_cbSampleAveraged.Text);
                    UpdateTimimgParams();
                }

                if (m_params.m_channelsTab != null)
                {
                    m_params.m_channelsTab.UpdateConvTimeValues();
                }
            }
            else if (sender == m_cbAverageMode && m_params.GlobalEditMode)
            {
                m_params.AveragingMode = m_params.GetEnumValue<CyEAverageMode>(CyParamNames.AVERAGING_MODE,
                    m_cbAverageMode.Text);
            }
            else if (sender == m_cbAlterResolution)
            {
                if (m_params.GlobalEditMode)
                {
                    m_params.AlternateResolution = m_params.GetEnumValue<CyEAlternateResolution>(
                        CyParamNames.ALTERNATE_RESOLUTION, m_cbAlterResolution.Text);
                    m_params.UpdateMaxResolutionUsed();
                    if (m_params.m_channelsTab != null)
                    {
                        m_params.m_channelsTab.UpdateResolutionErrors();
                    }
                    UpdateTimimgParams();
                }

                if (m_params.m_channelsTab != null)
                {
                    m_params.m_channelsTab.UpdateConvTimeValues();
                }
            }
            else if (sender == m_cbSingleEndNegInput)
            {
                if (m_params.GlobalEditMode)
                {
                    m_params.SingleEndedNegativeInput = m_params.GetEnumValue<CyESingleEndedNegativeInput>(
                        CyParamNames.SINGLE_ENDED_NEGATIVE_INPUT, m_cbSingleEndNegInput.Text);
                }
                UpdateModeRanges();
                UpdateResultFormat();
                m_params.UpdateVnegVisibleParam();
            }
            else if (sender == m_cbVrefSel)
            {
                if (m_params.GlobalEditMode)
                {
                    m_params.VrefSelect = m_params.GetEnumValue<CyEVRefSelect>(CyParamNames.VREF_SELECT_TYPE,
                        m_cbVrefSel.Text);
                    AcquisitionTimesAdjustment();
                }

                if (((m_params.VrefSelect == CyEVRefSelect.InternalVref) ||
                     (m_params.VrefSelect == CyEVRefSelect.InternalVrefBypassed)) && 
                    (m_params.IsPSoC4s8srsslt == false))
                {
                    m_errorProvider.SetError(m_cbVrefSel, Resources.VrefSelectIncorrectValue);
                }
                else if (((m_params.VrefSelect == CyEVRefSelect.Internal1024) ||
                          (m_params.VrefSelect == CyEVRefSelect.Internal1024Bypassed)) &&
                          m_params.IsPSoC4s8srsslt)
                {
                    m_errorProvider.SetError(m_cbVrefSel, Resources.VrefSelectIncorrectValue);
                }
                else
                {
                    m_errorProvider.SetError(m_cbVrefSel, string.Empty);
                    UpdateVoltageRefControl();
                    UpdateModeRanges();
                }
                m_numUpDown_TextChanged(m_numClkFreq, null);
                UpdateSPSClockFrequencyRanges();     
            }
            else if (sender == m_cbCompareMode && m_params.GlobalEditMode)
            {
                m_params.CompareMode = m_params.GetEnumValue<CyECompareMode>(CyParamNames.COMPARE_MODE,
                    m_cbCompareMode.Text);
            }
        }

        private void rbScanRate_CheckedChanged(object sender, EventArgs e)
        {
            if (m_params.GlobalEditMode)
            {
                m_params.AdjustType = m_rbSampleRate.Checked ? CyEAdjust.ScanRate : CyEAdjust.ClockFreq;

                m_numScanRate.Enabled = m_params.AdjustType == CyEAdjust.ScanRate;
                m_numClkFreq.Enabled = m_params.AdjustType == CyEAdjust.ClockFreq;
            }
        }

        private void rbInternal_CheckedChanged(object sender, EventArgs e)
        {
            if (m_params.GlobalEditMode)
            {
                m_params.ClockSourceType = m_rbInternal.Checked ? CyESarAdcClockSrc.Internal :
                    CyESarAdcClockSrc.External;
                UpdateClockData(m_params.InstQuery, m_params.TermQuery);
            }
        }

        private void rbSampleMode_CheckedChanged(object sender, EventArgs e)
        {
            if (m_params.GlobalEditMode)
            {
                if (m_rbFreeRun.Checked == true)
                {
                    m_params.SampleModeType = CyESampleMode.FreeRunning;
                }
                else
                {
                    m_params.SampleModeType = CyESampleMode.HardwareSOC;
                }
            }
        }

        /// <summary>
        /// This method updates UI depending on external clock changes
        /// </summary>
        /// <param name="query">Reference to ICyInstQuery_v1 instance</param>
        /// <param name="termQuery">Reference to ICyTerminalQuery_v1 instance</param>
        public void UpdateClockData(ICyInstQuery_v1 query, ICyTerminalQuery_v1 termQuery)
        {
            UpdateTimingControlsVisibility();

            if (m_params.ClockSourceType == CyESarAdcClockSrc.External)
            {
                double clkFreq = CyClock.GetClockFrequencyHz(m_params.TermQuery, false, CyClock.INTERNAL_CLOCK_OR_GATE_NAME);
                if (CyClock.IsFrequencyKnown(clkFreq))
                {
                    m_numClkFreq.Text = (clkFreq / 1000.0).ToString();
                    string sampleRate = m_params.GetSampleRate(clkFreq).ToString() + " SPS";
                    m_numScanRate.Text = sampleRate;
                    m_lblActualSampleRate.Text = sampleRate;
                    m_lblActualClockFrequency.Text = Math.Round(clkFreq / 1000.0 , 0).ToString() + " kHz";
                }
                m_errorProvider.SetError(m_lblActualClockFrequency, string.Empty); 
            }
            else
            {
                double clkFreq = CyClock.GetClockFrequencyHz(m_params.TermQuery, true, CyClock.INTERNAL_CLOCK_OR_GATE_NAME);
                if (CyClock.IsFrequencyKnown(clkFreq))
                {
                    m_lblActualSampleRate.Text = m_params.GetSampleRate(clkFreq).ToString() + " SPS";
                    m_lblActualClockFrequency.Text = Math.Round(clkFreq / 1000.0, 0).ToString() + " kHz"; 
                    m_errorProvider.SetError(m_lblActualClockFrequency, m_params.GetActualClockFrequencyValueError(clkFreq));                     
                    UpdateSPSClockFrequencyRanges();
                }
            }

            if (m_numClkFreq.Visible)
            {
                m_errorProvider.SetError(m_numClkFreq, m_params.GetClockFrequencyError(m_params.ClockFrequency));
            }
            else
            {
                m_errorProvider.SetError(m_numClkFreq, "");
            }
        }

        /// <summary>
        /// This method Adjust Acquisition Times depending on selected Vref and clock frequency
        /// By default value 4 is selected along with "bypassed" mode for Acquisition Times. 
        /// When mode changed to "not bypassed" and the calculated Clock frequency will become greater than 1.6 Mhz, 
        /// customiser automatically changed "Acquisition times" parameter to the "2" for all channels.
        /// </summary>        
        private void AcquisitionTimesAdjustment()
        {
            if (m_params.IsReferenceNotBypassed() &&
                (m_params.ClockFrequency - CyParameters.EPS >= CyParamRanges.MAX_CLOCK_FREQ_NOT_BYPASSED_KHZ * 1000))
            {
                m_params.AClock = CyParamRanges.ACQUISITION_TIME_ADJUST_VALUE;
                m_params.BClock = CyParamRanges.ACQUISITION_TIME_ADJUST_VALUE;
                m_params.CClock = CyParamRanges.ACQUISITION_TIME_ADJUST_VALUE;
                m_params.DClock = CyParamRanges.ACQUISITION_TIME_ADJUST_VALUE;

                m_params.m_channelsTab.UpdateUI();
            }
        }
        #endregion

        #region Public Methods
        public void UpdateAvgLeftDataComboBoxError()
        {
            if (m_params.m_channelsTab.GetEnabledAvgNum() != 0 &&
                m_params.DataFormatJustification == CyEFormatJustify.Left)
            {
                errorProviderNotCreator.SetError(m_cbDataFormatJustify, Resources.LeftJustificationAvgError);
            }
            else
            {
                errorProviderNotCreator.SetError(m_cbDataFormatJustify, string.Empty);
            }
        }
        #endregion Public Methods
    }
}
