/*******************************************************************************
* Copyright 2008-2013, Cypress Semiconductor Corporation.  All rights reserved.
* You may use this file only in accordance with the license, terms, conditions, 
* disclaimers, and limitations in the end user license agreement accompanying 
* the software package with which this file was provided.
********************************************************************************/


using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Drawing;
using System.Data;
using System.Text;
using System.Windows.Forms;
using System.Diagnostics;

namespace WaveDAC8_v2_10
{
    public partial class CyWaveformControl : UserControl
    {
        #region Fields
        private int m_waveformNumber;
        public int WaveformNumber
        {
            get { return m_waveformNumber; }
        }

        private CyParameters m_parameters;

        private CyWaveformChart m_waveChart;
        #endregion Fields

        #region Constructors
        public CyWaveformControl()
        {
            InitializeComponent();
        }

        public CyWaveformControl(int waveformNumber, CyParameters parameters)
            : this()
        {
            m_waveformNumber = waveformNumber;
            m_parameters = parameters;

            m_waveChart = new CyWaveformChart(m_waveformNumber, m_parameters);
            m_pnlGraph.Controls.Add(m_waveChart);
            m_waveChart.Dock = DockStyle.Fill;

            m_gbWaveform.Text = cywavedacresource.GroupBoxWaveformTitle + WaveformNumber;
            CyAuxFunctions.FillComboFromEnum(m_cbWaveType, typeof(CyEWaveFormType));

            m_cbWaveType.SelectedIndexChanged += cbWaveType_SelectedIndexChanged;
            m_nudAmplitude.TextChanged += nud_TextChanged;
            m_nudDCOffset.TextChanged += nud_TextChanged;
            m_nudNumSamples.TextChanged += nud_TextChanged;
            m_nudDegreeShift.TextChanged += nud_TextChanged;
            m_waveChart.ArbWaveChanged += m_waveChart_ArbWaveChanged;
        }
        #endregion Constructors

        #region Update UI
        public void UpdateUIFromParams()
        {
            UpdateVoltageRange(false);

            CyAuxFunctions.SetComboValue(m_cbWaveType, m_parameters.GetWaveType(WaveformNumber));
            CyAuxFunctions.SetNudValue(m_nudAmplitude, (decimal)m_parameters.GetWaveAmplitude(WaveformNumber));
            CyAuxFunctions.SetNudValue(m_nudDCOffset, (decimal)m_parameters.GetWaveDCOffset(WaveformNumber));
            CyAuxFunctions.SetNudValue(m_nudDegreeShift, m_parameters.GetWaveDegreeShift(WaveformNumber));
            CyAuxFunctions.SetNudValue(m_nudNumSamples,m_parameters.GetWaveNumSamples(WaveformNumber));
        }
        #endregion Update UI

        #region Public functions
        public void UpdateSampleRate(UInt32 sampleRate)
        {
            m_waveChart.SPS = sampleRate;
            m_waveChart.RefreshAll();
        }

        public void UpdateVoltageRange(bool adjustAmplitude)
        {
            CyWaveRange range = m_parameters.GetMaxVolage();
            m_waveChart.SetWaveRange(range);
            ConfigureNumerics();

            if (adjustAmplitude)
            {
                m_nudAmplitude.Value = (decimal)range.DefaultValue;
                m_nudDCOffset.Value = m_nudAmplitude.Maximum / 2;
            }

            CreateWaveform();
            m_waveChart.RefreshAll();
        }

        public Size GetMinSize()
        {
            int offset = 5;
            int width = m_lblDegreeShift.Left + m_lblDegreeShift.Width + offset;
            int height = m_nudNumSamples.Top + m_nudNumSamples.Height + offset;
            return new Size(width, height);
        }
        #endregion Public functions

        #region Private functions
        private Nullable<T> ValidateNumericValue<T>(Control sender, T min, T max) where T : struct, IConvertible, 
                                                                                            IComparable<T>
        {
            bool wrongFormat;
            string errorMessage = "";
            bool outOfRange = false;
            T nudValue = CyAuxFunctions.GetNumUpDownTextValue<T>(sender, out wrongFormat, ref errorMessage);

            if (wrongFormat == false)
            {
                if (nudValue.CompareTo(min) < 0 || nudValue.CompareTo(max) > 0)
                {
                    errorMessage = String.Format(cywavedacresource.MsgOutOfRange, min, max);
                    outOfRange = true;
                }
            }
            if (wrongFormat || outOfRange)
            {
                errorProvider.SetError(sender, string.Format(errorMessage));
                return null;
            }
            else
            {
                errorProvider.SetError(sender, string.Empty);
                return nudValue;
            }
        }

        private void ConfigureNumerics()
        {
            CyWaveRange range = m_parameters.GetMaxVolage();
            double maxValue = range.MaxRange;
            double minValue = 0;
            int decimalPlaces = 3;
            m_nudAmplitude.Increment = Convert.ToDecimal(maxValue / CyParamConst.MAX_DATA_VALUE);
            m_nudDCOffset.Increment = Convert.ToDecimal(maxValue / CyParamConst.MAX_DATA_VALUE);
            m_nudAmplitude.Maximum = Convert.ToDecimal(maxValue);
            m_nudDCOffset.Maximum = Convert.ToDecimal(maxValue);
            m_nudDCOffset.Minimum = Convert.ToDecimal(minValue);
            m_nudDCOffset.DecimalPlaces = decimalPlaces;
            m_nudAmplitude.DecimalPlaces = decimalPlaces;
            m_lblAmp.Text = String.Format(cywavedacresource.AmplitudeLabelText, range.UnitsPP);
            m_lblDCOff.Text = String.Format(cywavedacresource.OffsetLabelText, range.Units);
        }

        private void CreateWaveform()
        {
            double maxVoltage = m_parameters.GetMaxVolage().MaxRange;
            uint numSamples = m_parameters.GetWaveNumSamples(WaveformNumber);
            double amplitude = m_parameters.GetWaveAmplitude(WaveformNumber);
            double dcOffset = m_parameters.GetWaveDCOffset(WaveformNumber);
            ushort degreeShift = m_parameters.GetWaveDegreeShift(WaveformNumber);
            CyEWaveFormType waveformType = m_parameters.GetWaveType(WaveformNumber);
            List<byte> data = new List<byte>();

            switch (waveformType)
            {
                case CyEWaveFormType.Sine:
                case CyEWaveFormType.Triangle:
                case CyEWaveFormType.Sawtooth:
                case CyEWaveFormType.Square:
                    data = CyAuxFunctions.CreateWaveform(waveformType, numSamples, maxVoltage, amplitude, dcOffset, 
                                                         degreeShift);
                    break;
                case CyEWaveFormType.ArbitraryDraw:
                case CyEWaveFormType.ArbitraryFromFile:
                    data = m_parameters.GetWaveData(WaveformNumber);
                    break;
                default:
                    Debug.Fail(String.Empty);
                    break;
            }
            m_parameters.SetWaveData(WaveformNumber, data);
            m_waveChart.DataValues = new List<byte>(data);
            m_waveChart.RefreshChart();
        }

        private void UpdateVisibility()
        {
            if ((m_parameters.GetWaveType(WaveformNumber) == CyEWaveFormType.ArbitraryDraw) ||
                (m_parameters.GetWaveType(WaveformNumber) == CyEWaveFormType.ArbitraryFromFile))
            {
                m_nudAmplitude.Enabled = false;
                m_nudDCOffset.Enabled = false;
                m_nudDegreeShift.Enabled = false;
            }
            else
            {
                m_nudAmplitude.Enabled = true;
                m_nudDCOffset.Enabled = true;
                m_nudDegreeShift.Enabled = true;
            }

            if (m_parameters.GetWaveType(WaveformNumber) == CyEWaveFormType.ArbitraryFromFile)
            {
                m_nudNumSamples.Enabled = false;
            }
            else
            {
                m_nudNumSamples.Enabled = true;
            }
        }

        private void ChangeDataSize()
        {
            List<byte> data = m_waveChart.DataValues;
            int newNumberOfSamples = (int)m_parameters.GetWaveNumSamples(WaveformNumber);
            if (newNumberOfSamples > data.Count)
            {
                for (int i = data.Count; i < newNumberOfSamples; i++)
                {
                    data.Add((byte)0);
                }
            }
            else
            {
                data.RemoveRange(newNumberOfSamples, data.Count - newNumberOfSamples);
            }
            m_parameters.SetWaveData(WaveformNumber, data);
        }

        private void ImportWaveform()
        {
            List<byte> data = CyAuxFunctions.Import();
            if (data != null)
            {
                m_nudNumSamples.Value = data.Count;
            }
            else
            {
                // Set default data value (0)
                data = new List<byte>();
                uint numberOfSamples = m_parameters.GetWaveNumSamples(WaveformNumber);
                for (int i = 0; i < numberOfSamples; i++)
                {
                    data.Add(0);
                }
            }
            m_waveChart.DataValues = data;
            m_parameters.SetWaveData(WaveformNumber, data);
        }
        #endregion Private functions

        #region Event handlers
        private void cbWaveType_SelectedIndexChanged(object sender, EventArgs e)
        {
            CyEWaveFormType selectedValue = CyAuxFunctions.GetComboValue<CyEWaveFormType>(m_cbWaveType);

            // Show Browse button in Arbitrary from file mode
            m_btnBrowse.Visible = (selectedValue == CyEWaveFormType.ArbitraryFromFile);
            // Import waveform from file if ArbitraryFromFile option was chosen
            if ((selectedValue == CyEWaveFormType.ArbitraryFromFile) &&
                (m_parameters.GetWaveType(WaveformNumber) != selectedValue))
            {
                ImportWaveform();
            }
            
            m_parameters.SetWaveType(WaveformNumber, selectedValue);
            UpdateVisibility();
            CreateWaveform();
        }

        /// <summary>
        /// This event handler is assigned to all numUpDown controls
        /// </summary>
        private void nud_TextChanged(object sender, EventArgs e)
        {
            NumericUpDown nud = sender as NumericUpDown;
            if (sender == m_nudAmplitude)
            {
                double? nudValue = ValidateNumericValue<double>(nud, (double)nud.Minimum, (double)nud.Maximum);
                if (nudValue.HasValue)
                    m_parameters.SetWaveAmplitude(WaveformNumber, nudValue.Value);
            }
            else if (sender == m_nudDCOffset)
            {
                double? nudValue = ValidateNumericValue<double>(nud, (double)nud.Minimum, (double)nud.Maximum);
                if (nudValue.HasValue)
                    m_parameters.SetWaveDCOffset(WaveformNumber, nudValue.Value);
            }
            else if (sender == m_nudDegreeShift)
            {
                ushort? nudValue = ValidateNumericValue<ushort>(nud, (ushort)nud.Minimum, (ushort)nud.Maximum);
                if (nudValue.HasValue)
                    m_parameters.SetWaveDegreeShift(WaveformNumber, (ushort)nudValue);
            }
            else if (sender == m_nudNumSamples)
            {
                int? nudValue = ValidateNumericValue<int>(nud, (int)nud.Minimum, (int)nud.Maximum);
                if (nudValue.HasValue)
                    m_parameters.SetWaveNumSamples(WaveformNumber, (uint)nudValue.Value);
                ChangeDataSize();
                m_waveChart.RefreshAll();
            }

            CreateWaveform();
        }

        /// <summary>
        /// Set the number of decimal places in numericUpDown depending on entered value.
        /// </summary>
        private void nudDCOffset_ValueChanged(object sender, EventArgs e)
        {
            const byte DECIMAL_PLACES_EXTENDED = 4;
            const byte DECIMAL_PLACES_NORMAL = 3;
            if ((double)Math.Abs(m_nudDCOffset.Value - Math.Round(m_nudDCOffset.Value, DECIMAL_PLACES_NORMAL)) >=
                CyParamConst.EPS)
            {
                m_nudDCOffset.DecimalPlaces = DECIMAL_PLACES_EXTENDED;
            }
            else
            {
                m_nudDCOffset.DecimalPlaces = DECIMAL_PLACES_NORMAL;
            }
        }

        void m_waveChart_ArbWaveChanged(object sender, CyArbWaveChangedEventArgs e)
        {
            m_parameters.SetWaveData(WaveformNumber, e.Data);
        }

        private void btnBrowse_Click(object sender, EventArgs e)
        {
            ImportWaveform();
            CreateWaveform();
        }
        #endregion Event handlers
    }
}
