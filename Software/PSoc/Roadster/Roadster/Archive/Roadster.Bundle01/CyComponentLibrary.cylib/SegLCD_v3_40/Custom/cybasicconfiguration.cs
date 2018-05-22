/*******************************************************************************
* Copyright 2008-2012, Cypress Semiconductor Corporation.  All rights reserved.
* You may use this file only in accordance with the license, terms, conditions, 
* disclaimers, and limitations in the end user license agreement accompanying 
* the software package with which this file was provided.
********************************************************************************/

using System;
using System.Collections.Generic;
using System.Diagnostics;
using System.Windows.Forms;

namespace SegLCD_v3_40
{
    public partial class CyBasicConfiguration : CyEditingWrapperControl
    {
        private static readonly byte[] MODE_INDEXES_COMBOBOX = { 2, 0, 1 };
        public enum CyMode
        {
            NOSLEEP, LOW_POWER_ILO, LOW_POWER_32K
        } ;
        private const int FRAME_RATE_MAX = 150;
        private const int BIAS_VOLTAGE_ITEM_COUNT = 64;

        private readonly bool m_internalChanges;
        private List<uint> m_frameRateRange = new List<uint>();

        public CyBasicConfiguration()
        {
            InitializeComponent();
        }


        public CyBasicConfiguration(CyLCDParameters parameters)
            : base(parameters)
        {
            InitializeComponent();

            m_parameters.m_cyBasicConfigurationTab = this;

            m_internalChanges = true;
            if (m_parameters.SupplyType == (byte)CyLCDParameters.CySupplyType.V3)
                radioButton3V.Checked = true;
            else
                radioButton5V.Checked = true;
            InitFrameRateComboBox();
            InitBiasVoltageComboBox();
            LoadValuesFromParameters();

            numUpDownNumCommonLines.TextChanged += numUpDown_TextChanged;
            numUpDownNumSegmentLines.TextChanged += numUpDown_TextChanged;

            m_internalChanges = false;
        }

        public void LoadValuesFromParameters()
        {
            // For compatibility with previous versions, check if number of segments don't exceed max numUpDown value
            if (numUpDownNumSegmentLines.Maximum < m_parameters.NumSegmentLines)
            {
                numUpDownNumSegmentLines.Maximum = m_parameters.NumSegmentLines;
            }

            numUpDownNumCommonLines.Value = m_parameters.NumCommonLines;
            numUpDownNumSegmentLines.Value = m_parameters.NumSegmentLines;
            comboBoxWaveformType.SelectedIndex = m_parameters.WaveformType;

            if (comboBoxFrameRate.Items.Contains(m_parameters.FrameRate))
                comboBoxFrameRate.Text = m_parameters.FrameRate.ToString();
            else
                comboBoxFrameRate.SelectedIndex = comboBoxFrameRate.Items.Count - 1;

            if (m_parameters.BiasVoltage < BIAS_VOLTAGE_ITEM_COUNT - comboBoxBiasVoltage.Items.Count)
            {
                comboBoxBiasVoltage.SelectedIndex = 0;
            }
            else if (m_parameters.BiasVoltage < BIAS_VOLTAGE_ITEM_COUNT )
                comboBoxBiasVoltage.SelectedIndex = m_parameters.BiasVoltage - BIAS_VOLTAGE_ITEM_COUNT +
                                                    comboBoxBiasVoltage.Items.Count;
            else
                comboBoxBiasVoltage.SelectedIndex = comboBoxBiasVoltage.Items.Count - 1;

            checkBoxGang.Checked = m_parameters.Gang;
            comboBoxBiasType.SelectedIndex = m_parameters.BiasType;
            comboBoxDriverPowerMode.SelectedIndex = MODE_INDEXES_COMBOBOX[m_parameters.DriverPowerMode];
        }

        private void InitFrameRateComboBox()
        {
            double max = GetFrameRateMaximum();
            comboBoxFrameRate.Items.Clear();
            m_frameRateRange.Clear();
            if ((m_parameters.DriverPowerMode == (byte)CyMode.LOW_POWER_32K) ||
                (m_parameters.DriverPowerMode == (byte)CyMode.LOW_POWER_ILO))
            {
                int i = 2;
                while ((max / i > 10) && (i <= 255))
                {
                    m_frameRateRange.Insert(0, (uint)(max / i++));
                    // Check max
                    if (m_frameRateRange[0] <= FRAME_RATE_MAX)
                        // Check step
                        if ((comboBoxFrameRate.Items.Count == 0) ||
                            ((comboBoxFrameRate.Items.Count > 0) &&
                            ((byte)comboBoxFrameRate.Items[0] - m_frameRateRange[0] >= 5)))
                        {
                            comboBoxFrameRate.Items.Insert(0, (byte)m_frameRateRange[0]);
                        }
                }
            }
            else
            {
                for (int i = 10; i <= max; i += 10)
                {
                    m_frameRateRange.Add((uint)i);
                    comboBoxFrameRate.Items.Add((byte) i);
                }
            }
        }

        private void InitBiasVoltageComboBox()
        {
            const double EPS = 0.00000001;
            comboBoxBiasVoltage.Items.Clear();
            const double SUPPLY_3V = 3.0, SUPPLY_5V = 5.5;
            double supply = radioButton3V.Checked ? SUPPLY_3V : SUPPLY_5V;
            double step = 0.0273 * supply / 3;
            for (int i = 0; i < 64; i++)
            {
                double res = supply - i*step;
                string sres = radioButton3V.Checked ? res.ToString("f3") : res.ToString("f2");
                if (res > 2.0 - EPS)
                    comboBoxBiasVoltage.Items.Insert(0, sres);
            }
        }

        private void UpdateFrameRateMax()
        {
            InitFrameRateComboBox();
           
            if (m_parameters.FrameRate >= (byte)comboBoxFrameRate.Items[comboBoxFrameRate.Items.Count - 1])
            {
                m_parameters.FrameRate = (byte)comboBoxFrameRate.Items[comboBoxFrameRate.Items.Count - 1];
            }
            else if ((m_parameters.FrameRate <= (byte) comboBoxFrameRate.Items[0]))
            {
                m_parameters.FrameRate = (byte) comboBoxFrameRate.Items[0];
            }
            else
            {
                for (int i = 0; i < comboBoxFrameRate.Items.Count - 1; i++)
                {
                    byte highLimit = Convert.ToByte(comboBoxFrameRate.Items[i + 1]);
                    byte lowLimit = Convert.ToByte(comboBoxFrameRate.Items[i]);
                    if ((m_parameters.FrameRate <= highLimit) && (m_parameters.FrameRate >= lowLimit))
                    {
                        m_parameters.FrameRate = highLimit - m_parameters.FrameRate < m_parameters.FrameRate - lowLimit
                                                     ? highLimit
                                                     : lowLimit;
                        break;
                    }
                }
            }
            comboBoxFrameRate.SelectedIndex = comboBoxFrameRate.Items.IndexOf(m_parameters.FrameRate);
        }

        private void numUpDownNumLines_ValueChanged(object sender, EventArgs e)
        {
            bool isCommonChanged = sender == numUpDownNumCommonLines;
            NumericUpDown numUpDown = (NumericUpDown) sender;
            byte paramValue = isCommonChanged ? m_parameters.NumCommonLines : m_parameters.NumSegmentLines;

            bool updateHelpers = numUpDown.Value != paramValue;

            if (paramValue != (byte)numUpDown.Value)
            {
                if (isCommonChanged)
                {
                    m_parameters.NumCommonLines = (byte) numUpDown.Value;
                    SetBiasType();
                }
                else
                    m_parameters.NumSegmentLines = (byte)numUpDown.Value;
                m_parameters.m_cyDriverParamsTab.UpdateStrength();
            }

            if (isCommonChanged)
            {
                UpdateFrameRateMax();
                SetClockFrequency();
            }

            //Update Empty helper
            if (updateHelpers)
            {
                m_parameters.m_cyHelpersTab.ComSegLinesNumChanged();
            }
        }

        void numUpDown_TextChanged(object sender, EventArgs e)
        {
            UpdateNumericErrorProvider((NumericUpDown)sender, m_errorProvider);
        }

        private void SetBiasType()
        {
            if (m_internalChanges) return;

            int value = (int)numUpDownNumCommonLines.Value;
            if ((value >= 2) && (value <= 6))
            {
                comboBoxBiasType.SelectedIndex = 0;
            }
            else if ((value >= 7) && (value <= 11))
            {
                comboBoxBiasType.SelectedIndex = 1;
            }
            else // 12-16
            {
                comboBoxBiasType.SelectedIndex = 2;
            }
        }

        private void SetClockFrequency()
        {
            m_parameters.ClockFrequency = Convert.ToUInt32(Math.Ceiling(
                                          (m_parameters.WaveformType == (byte)CyLCDParameters.CyWaveformType.A)
                                          ? (m_parameters.NumCommonLines)*m_parameters.FrameRate*512*1.075
                                          : (m_parameters.NumCommonLines)*m_parameters.FrameRate*256*1.075));
            SetDefaultValuesHiLowDriveTime();
        }

        private double GetFrameRateMaximum()
        {
            double max = FRAME_RATE_MAX;
            const double LP_ILO_CONST = 1000;
            const double LP_32K_CONST = 8000;
            if (m_parameters.DriverPowerMode == (byte)CyMode.LOW_POWER_ILO)
            {
                if (m_parameters.WaveformType == (byte)CyLCDParameters.CyWaveformType.A)
                {
                    max = LP_ILO_CONST / (2 * m_parameters.NumCommonLines);
                }
                else
                {
                    max = LP_ILO_CONST / m_parameters.NumCommonLines;
                }
                     
            }
            else if (m_parameters.DriverPowerMode == (byte)CyMode.LOW_POWER_32K)
            {
                if (m_parameters.WaveformType == (byte)CyLCDParameters.CyWaveformType.A)
                {
                    max = LP_32K_CONST / (2 * m_parameters.NumCommonLines);
                }
                else
                {
                    max = LP_32K_CONST / m_parameters.NumCommonLines;
                }
            }
            return max;
        }

        private void comboBoxWaveformType_SelectedIndexChanged(object sender, EventArgs e)
        {
            m_parameters.WaveformType = (byte)comboBoxWaveformType.SelectedIndex;
            SetClockFrequency();
            UpdateFrameRateMax();
        }

        private void comboBoxFrameRate_SelectedIndexChanged(object sender, EventArgs e)
        {
            m_parameters.FrameRate = Convert.ToByte(comboBoxFrameRate.Text);
            if (comboBoxFrameRate.SelectedIndex >= 0)
            {
                m_parameters.TimerPeriod =
                    Convert.ToByte(m_frameRateRange.Count - m_frameRateRange.IndexOf(
                                   (byte) comboBoxFrameRate.Items[comboBoxFrameRate.SelectedIndex]));                
            }
            SetClockFrequency();
        }

        private void comboBoxBiasVoltage_SelectedIndexChanged(object sender, EventArgs e)
        {
            m_parameters.BiasVoltage =
                (byte) (comboBoxBiasVoltage.SelectedIndex + BIAS_VOLTAGE_ITEM_COUNT - comboBoxBiasVoltage.Items.Count);
            SetDefaultValuesHiLowDriveTime();
        }

        private void checkBoxGang_CheckedChanged(object sender, EventArgs e)
        {
            m_parameters.Gang = checkBoxGang.Checked;
        }

        private void comboBoxBiasType_SelectedIndexChanged(object sender, EventArgs e)
        {
            m_parameters.BiasType = (byte)comboBoxBiasType.SelectedIndex;
        }

        private void comboBoxDriverPowerMode_SelectedIndexChanged(object sender, EventArgs e)
        {
            m_parameters.DriverPowerMode =
                (byte)(new List<byte>(MODE_INDEXES_COMBOBOX)).IndexOf((byte)comboBoxDriverPowerMode.SelectedIndex);

            if (m_parameters.DriverPowerMode == (byte)CyMode.NOSLEEP)
            {
                m_parameters.UseCustomStep = false;
            }

            SetDefaultValuesHiLowDriveTime();
            UpdateFrameRateMax();
            m_parameters.ClockFrequencyGeneral = 0; // SetParamExpr
        }

        public void SetDefaultValuesHiLowDriveTime()
        {
            const byte MAX_DRIVE_TIME = 254;
            const byte MIN_DRIVE_TIME = 1;

            if (m_internalChanges)
                return;

            if (m_parameters.AdvancedSettings)
            {
                if (m_parameters.DriverPowerMode != (byte)CyMode.NOSLEEP)
                    m_parameters.LowDriveInitTime = MIN_DRIVE_TIME;
                return;
            }

            // HighDriveTime
            // Formula: HighDriveTime = (1500pF * TotalActiveArea * BiasVoltage) / (NumCommons * BufferOutputCurrent)
            const double BUF_OUT_CURRENT_3V = 300;
            const double BUF_OUT_CURRENT_5V = 355;
            const double CAPACITY = 1500;
            double totalActiveArea = m_parameters.GlassSize / 2.0;
            double bufferOutputCurrent = (m_parameters.SupplyType == (byte)CyLCDParameters.CySupplyType.V3) ?
                                         BUF_OUT_CURRENT_3V : BUF_OUT_CURRENT_5V;
            double biasVoltage;
            if (double.TryParse(comboBoxBiasVoltage.Text, out biasVoltage) == false)
            {
                return;
            }

            double hiDriveTime = (CAPACITY * totalActiveArea * biasVoltage) / 
                                 (m_parameters.NumCommonLines * bufferOutputCurrent);
            int hiDriveTimeInt = (int)Math.Ceiling(hiDriveTime / (double)m_parameters.DefaultClockPeriod);
            if (hiDriveTimeInt > byte.MaxValue)
            {
                Debug.Assert(false);
            }
            m_parameters.HiDriveTime = (byte)hiDriveTimeInt;

            // LowDriveTime

            if (m_parameters.DriverPowerMode == (byte)CyMode.NOSLEEP)
            {
                m_parameters.LowDriveInitTime = (byte)(MAX_DRIVE_TIME - m_parameters.HiDriveTime);
            }
            else
            {
                m_parameters.LowDriveInitTime = MIN_DRIVE_TIME;
            }
        }

        private void radioButton3V_CheckedChanged(object sender, EventArgs e)
        {
            if (m_internalChanges) return;

            if (((RadioButton)sender).Checked)
            {
                InitBiasVoltageComboBox();
                if (m_parameters.BiasVoltage < BIAS_VOLTAGE_ITEM_COUNT - comboBoxBiasVoltage.Items.Count)
                    comboBoxBiasVoltage.SelectedIndex = 0;
                else if (m_parameters.BiasVoltage < BIAS_VOLTAGE_ITEM_COUNT)
                    comboBoxBiasVoltage.SelectedIndex = m_parameters.BiasVoltage -
                                                        (BIAS_VOLTAGE_ITEM_COUNT - comboBoxBiasVoltage.Items.Count);
                else
                    comboBoxBiasVoltage.SelectedIndex = comboBoxBiasVoltage.Items.Count - 1;

                m_parameters.SupplyType = radioButton3V.Checked ? (byte)CyLCDParameters.CySupplyType.V3 : 
                                                                  (byte)CyLCDParameters.CySupplyType.V5;

                SetDefaultValuesHiLowDriveTime();
            }
        }

        public static void UpdateNumericErrorProvider(NumericUpDown numUpDown, ErrorProvider errorProvider)
        {
            string text = numUpDown.Text;
            int parsedValue;
            bool parsed = Int32.TryParse(text, out parsedValue);

            if (parsed && (parsedValue >= (int)numUpDown.Minimum) && (parsedValue <= (int)numUpDown.Maximum))
            {
                errorProvider.SetError(numUpDown, "");
            }
            else
            {
                errorProvider.SetError(numUpDown, String.Format(Properties.Resources.FORMAT_ERROR_MSG, 
                    Math.Round(numUpDown.Minimum, numUpDown.DecimalPlaces), 
                    Math.Round(numUpDown.Maximum, numUpDown.DecimalPlaces)));
            }
        }
    }
}

