/*******************************************************************************
* Copyright 2008-2013, Cypress Semiconductor Corporation.  All rights reserved.
* You may use this file only in accordance with the license, terms, conditions, 
* disclaimers, and limitations in the end user license agreement accompanying 
* the software package with which this file was provided.
********************************************************************************/

using System;
using System.Windows.Forms;
using System.Diagnostics;
using CyDesigner.Extensions.Gde;
using Cypress.Comps.PinsAndPorts.Common_v1_90;

namespace Cypress.Comps.PinsAndPorts.cy_pins_v1_90
{
    public partial class CyOutputControl : UserControl
    {
        CyPerPinDataControl m_perPinDataControl;
        private ICyInstEdit_v1 m_instEdit;

        public CyPerPinDataControl PerPinDataControl
        {
            get { return m_perPinDataControl; }
            set { m_perPinDataControl = value; }
        }

        public CyOutputControl(ICyInstEdit_v1 instEdit)
        {
            InitializeComponent();

            m_instEdit = instEdit;

            m_slewRateComboBox.DropDownStyle = ComboBoxStyle.DropDownList;
            m_slewRateComboBox.Items.Add(new CySlewRate(CySlewRate.CyRate.Slow));
            m_slewRateComboBox.Items.Add(new CySlewRate(CySlewRate.CyRate.Fast));

            m_driveLevelComboBox.DropDownStyle = ComboBoxStyle.DropDownList;
            m_driveLevelComboBox.Items.Add(new CyDriveLevel(CyDriveLevel.CyLevel.Vddio));
            m_driveLevelComboBox.Items.Add(new CyDriveLevel(CyDriveLevel.CyLevel.Vref));

            m_currentComboBox.DropDownStyle = ComboBoxStyle.DropDownList;
            m_currentComboBox.Items.Add(new CyDriveCurrent(CyDriveCurrent.CyCurrent.Source4Sink8));
            m_currentComboBox.Items.Add(new CyDriveCurrent(CyDriveCurrent.CyCurrent.Source4Sink25));

            m_outputModeComboBox.DropDownStyle = ComboBoxStyle.DropDownList;
            m_outputModeComboBox.Items.Add(new CyOutputMode(CyOutputMode.CyOutMode.Transparent));
            m_outputModeComboBox.Items.Add(new CyOutputMode(CyOutputMode.CyOutMode.SingleSync));
            if (instEdit.DeviceQuery.IsPSoC4)
            {
                m_outputModeComboBox.Items.Add(new CyOutputMode(CyOutputMode.CyOutMode.ClockNormal));
                m_outputModeComboBox.Items.Add(new CyOutputMode(CyOutputMode.CyOutMode.ClockInverted));
            }

            m_oeSyncCheckBox.Visible = instEdit.DeviceQuery.IsPSoC4;


            m_oeSyncCheckBox.CheckedChanged += m_oeSyncCheckBox_CheckedChanged;
            m_slewRateComboBox.SelectedIndexChanged += m_slewRateComboBox_SelectedIndexChanged;
            m_driveLevelComboBox.SelectedIndexChanged += m_driveLevelComboBox_SelectedIndexChanged;
            m_currentComboBox.SelectedIndexChanged += m_currentComboBox_SelectedIndexChanged;
            m_outputModeComboBox.SelectedIndexChanged += m_outputModeComboBox_SelectedIndexChanged;
            m_errorProvider.SetIconAlignment(m_slewRateComboBox, ErrorIconAlignment.MiddleLeft);
            m_errorProvider.SetIconPadding(m_slewRateComboBox, 3);
            m_errorProvider.SetIconAlignment(m_driveLevelComboBox, ErrorIconAlignment.MiddleLeft);
            m_errorProvider.SetIconPadding(m_driveLevelComboBox, 3);
            m_errorProvider.SetIconAlignment(m_currentComboBox, ErrorIconAlignment.MiddleLeft);
            m_errorProvider.SetIconPadding(m_currentComboBox, 3);
            m_errorProvider.SetIconAlignment(m_oeSyncCheckBox, ErrorIconAlignment.MiddleLeft);
            m_errorProvider.SetIconPadding(m_oeSyncCheckBox, 3);
        }

        void m_currentComboBox_SelectedIndexChanged(object sender, EventArgs e)
        {
            PerPinDataControl.OnParamDataChangeByUser(new CyPerPinDataEventArgs(
                    CyParamInfo.Formal_ParamName_DriveCurrents, OutputDriveCurrent));
        }

        void m_driveLevelComboBox_SelectedIndexChanged(object sender, EventArgs e)
        {
            PerPinDataControl.OnParamDataChangeByUser(new CyPerPinDataEventArgs(
                CyParamInfo.Formal_ParamName_OutputDriveLevels, OutputDriveLevel));
        }

        void m_outputModeComboBox_SelectedIndexChanged(object sender, EventArgs e)
        {
            string outputSynchronized = OutputComboMode == CyPortConstants.OutputComboMode_DATA_TRANSPARENT
                                           ? CyPortConstants.OutputsSynchronizedValue_DISABLED
                                           : CyPortConstants.OutputsSynchronizedValue_ENABLED;

            string outputMode = OutputComboMode == CyPortConstants.OutputComboMode_DATA_TRANSPARENT ||
                                OutputComboMode == CyPortConstants.OutputComboMode_DATA_SINGLESYNC
                                    ? CyPortConstants.OutputModesValue_DATA
                                    : CyPortConstants.OutputModesValue_CLOCK;

            string outputAsClockMode = OutputComboMode == CyPortConstants.OutputComboMode_CLOCK_INVERTED
                                           ? CyPortConstants.OutputClockModesValue_INVERTED
                                           : CyPortConstants.OutputClockModesValue_NORMAL;

            PerPinDataControl.OnParamDataChangeByUser(new CyPerPinDataEventArgs(
                CyParamInfo.Formal_ParamName_OutputsSynchronized, outputSynchronized));
            PerPinDataControl.OnParamDataChangeByUser(new CyPerPinDataEventArgs(
                CyParamInfo.Formal_ParamName_OutputModes, outputMode));
            PerPinDataControl.OnParamDataChangeByUser(new CyPerPinDataEventArgs(
                CyParamInfo.Formal_ParamName_OutputClockModes, outputAsClockMode));
        }

        void m_oeSyncCheckBox_CheckedChanged(object sender, EventArgs e)
        {
            PerPinDataControl.OnParamDataChangeByUser(new CyPerPinDataEventArgs(
                CyParamInfo.Formal_ParamName_OESyncs, OESynchronized));
        }

        void m_slewRateComboBox_SelectedIndexChanged(object sender, EventArgs e)
        {
            PerPinDataControl.OnParamDataChangeByUser(new CyPerPinDataEventArgs(
                CyParamInfo.Formal_ParamName_SlewRate, SlewRate));
        }

        public string OutputComboModeErrorText
        {
            get { return m_errorProvider.GetError(m_outputModeComboBox); }
            set { m_errorProvider.SetError(m_outputModeComboBox, value); }
        }

        public string OESynchronized
        {
            get
            {
                if (m_oeSyncCheckBox.CheckState == CheckState.Indeterminate)
                {
                    return null;
                }
                return m_oeSyncCheckBox.Checked
                           ? CyPortConstants.OESyncsValue_SYNC
                           : CyPortConstants.OESyncsValue_NOSYNC;
            }

            set
            {
                m_oeSyncCheckBox.CheckedChanged -= m_oeSyncCheckBox_CheckedChanged;
                if (value == null)
                {
                    m_oeSyncCheckBox.CheckState = CheckState.Indeterminate;
                }
                else
                {
                    switch (value)
                    {
                        case CyPortConstants.OESyncsValue_NOSYNC:
                            m_oeSyncCheckBox.CheckState = CheckState.Unchecked;
                            m_oeSyncCheckBox.Checked = false;
                            break;

                        case CyPortConstants.OESyncsValue_SYNC:
                            m_oeSyncCheckBox.CheckState = CheckState.Checked;
                            m_oeSyncCheckBox.Checked = true;
                            break;

                        default:
                            m_oeSyncCheckBox.CheckState = CheckState.Indeterminate;
                            break;
                    }
                }
                m_oeSyncCheckBox.CheckedChanged += m_oeSyncCheckBox_CheckedChanged;
            }
        }

        public string OESynchronizedErrorText
        {
            get { return m_errorProvider.GetError(m_oeSyncCheckBox); }
            set { m_errorProvider.SetError(m_oeSyncCheckBox, value); }
        }

        public string SlewRate
        {
            get
            {
                CySlewRate slewRate = m_slewRateComboBox.SelectedItem as CySlewRate;
                return slewRate == null ? null : slewRate.ParamValue;
            }

            set
            {
                m_slewRateComboBox.SelectedIndexChanged -= m_slewRateComboBox_SelectedIndexChanged;
                if (value == null)
                {
                    m_slewRateComboBox.SelectedItem = null;
                }
                else
                {
                    switch (value)
                    {
                        case CyPortConstants.SlewRateValue_FAST:
                            Select(CySlewRate.CyRate.Fast);
                            break;

                        case CyPortConstants.SlewRateValue_SLOW:
                            Select(CySlewRate.CyRate.Slow);
                            break;

                        default:
                            m_slewRateComboBox.SelectedItem = null;
                            break;
                    }
                }
                m_slewRateComboBox.SelectedIndexChanged += m_slewRateComboBox_SelectedIndexChanged;
            }
        }

        public string SlewRateErrorText
        {
            get { return m_errorProvider.GetError(m_slewRateComboBox); }
            set { m_errorProvider.SetError(m_slewRateComboBox, value); }
        }

        public string OutputDriveLevel
        {
            get
            {
                CyDriveLevel driveLevel = m_driveLevelComboBox.SelectedItem as CyDriveLevel;
                return driveLevel == null ? null : driveLevel.ParamValue;
            }

            set
            {
                m_driveLevelComboBox.SelectedIndexChanged -= m_driveLevelComboBox_SelectedIndexChanged;
                if (value == null)
                {
                    m_driveLevelComboBox.SelectedItem = null;
                }
                else
                {
                    switch (value)
                    {
                        case CyPortConstants.OutputDriveLevelValue_VDDIO:
                            Select(CyDriveLevel.CyLevel.Vddio);
                            break;

                        case CyPortConstants.OutputDriveLevelValue_VREF:
                            Select(CyDriveLevel.CyLevel.Vref);
                            break;

                        default:
                            m_driveLevelComboBox.SelectedItem = null;
                            break;
                    }
                }
                m_driveLevelComboBox.SelectedIndexChanged += m_driveLevelComboBox_SelectedIndexChanged;
            }
        }

        public string OutputDriveLevelErrorText
        {
            get { return m_errorProvider.GetError(m_driveLevelComboBox); }
            set { m_errorProvider.SetError(m_driveLevelComboBox, value); }
        }

        public string OutputDriveCurrent
        {
            get
            {
                CyDriveCurrent driveCurrent = m_currentComboBox.SelectedItem as CyDriveCurrent;
                return driveCurrent == null ? null : driveCurrent.ParamValue;
            }

            set
            {
                m_currentComboBox.SelectedIndexChanged -= m_currentComboBox_SelectedIndexChanged;
                if (value == null)
                {
                    m_currentComboBox.SelectedItem = null;
                }
                else
                {
                    switch (value)
                    {
                        case CyPortConstants.DriveCurrentValue_4SOURCE_25SINK:
                            Select(CyDriveCurrent.CyCurrent.Source4Sink25);
                            break;

                        case CyPortConstants.DriveCurrentValue_4SOURCE_8SINK:
                            Select(CyDriveCurrent.CyCurrent.Source4Sink8);
                            break;

                        default:
                            m_currentComboBox.SelectedItem = null;
                            break;
                    }
                }
                m_currentComboBox.SelectedIndexChanged += m_currentComboBox_SelectedIndexChanged;
            }
        }

        public string OutputDriveCurrentErrorText
        {
            get { return m_errorProvider.GetError(m_currentComboBox); }
            set { m_errorProvider.SetError(m_currentComboBox, value); }
        }

        public string OutputComboMode
        {
            get
            {
                CyOutputMode mode = m_outputModeComboBox.SelectedItem as CyOutputMode;
                if (mode == null)
                {
                    return null;
                }
                if (mode.OutMode == CyOutputMode.CyOutMode.Transparent)
                    return CyPortConstants.OutputComboMode_DATA_TRANSPARENT;
                if (mode.OutMode == CyOutputMode.CyOutMode.SingleSync)
                    return CyPortConstants.OutputComboMode_DATA_SINGLESYNC;
                if (mode.OutMode == CyOutputMode.CyOutMode.ClockNormal)
                    return CyPortConstants.OutputComboMode_CLOCK_NORMAL;
                if (mode.OutMode == CyOutputMode.CyOutMode.ClockInverted)
                    return CyPortConstants.OutputComboMode_CLOCK_INVERTED;
                return null;
            }

            set
            {
                m_outputModeComboBox.SelectedIndexChanged -= m_outputModeComboBox_SelectedIndexChanged;
                if (value == null)
                {
                    m_outputModeComboBox.SelectedItem = null;
                }
                else
                {
                    switch (value)
                    {
                        case CyPortConstants.OutputComboMode_DATA_TRANSPARENT:
                            Select(CyOutputMode.CyOutMode.Transparent);
                            break;

                        case CyPortConstants.OutputComboMode_DATA_SINGLESYNC:
                            Select(CyOutputMode.CyOutMode.SingleSync);
                            break;

                        case CyPortConstants.OutputComboMode_CLOCK_NORMAL:
                            Select(CyOutputMode.CyOutMode.ClockNormal);
                            break;

                        case CyPortConstants.OutputComboMode_CLOCK_INVERTED:
                            Select(CyOutputMode.CyOutMode.ClockInverted);
                            break;

                        default:
                            m_outputModeComboBox.SelectedItem = null;
                            break;
                    }
                }
                m_outputModeComboBox.SelectedIndexChanged += m_outputModeComboBox_SelectedIndexChanged;
            }
        }

        void Select(CySlewRate.CyRate rate)
        {
            foreach (CySlewRate slewRate in m_slewRateComboBox.Items)
            {
                if (slewRate.SlewRate == rate)
                {
                    m_slewRateComboBox.SelectedItem = slewRate;
                    break;
                }
            }
        }

        void Select(CyDriveLevel.CyLevel level)
        {
            foreach (CyDriveLevel driveLevel in m_driveLevelComboBox.Items)
            {
                if (driveLevel.DriveLevel == level)
                {
                    m_driveLevelComboBox.SelectedItem = driveLevel;
                    break;
                }
            }
        }

        void Select(CyDriveCurrent.CyCurrent current)
        {
            foreach (CyDriveCurrent driveCurrent in m_currentComboBox.Items)
            {
                if (driveCurrent.DriveCurrent == current)
                {
                    m_currentComboBox.SelectedItem = driveCurrent;
                    break;
                }
            }
        }

        void Select(CyOutputMode.CyOutMode outMode)
        {
            foreach (CyOutputMode mode in m_outputModeComboBox.Items)
            {
                if (mode.OutMode == outMode)
                {
                    m_outputModeComboBox.SelectedItem = mode;
                    break;
                }
            }
        }

        class CySlewRate
        {
            public enum CyRate { Fast, Slow };

            CyRate m_rate;

            public CyRate SlewRate { get { return m_rate; } }

            public CySlewRate(CyRate rate)
            {
                m_rate = rate;
            }

            public string ParamValue
            {
                get
                {
                    switch (SlewRate)
                    {
                        case CyRate.Fast:
                            return CyPortConstants.SlewRateValue_FAST;

                        case CyRate.Slow:
                            return CyPortConstants.SlewRateValue_SLOW;

                        default:
                            Debug.Fail("unhandled");
                            return string.Empty;
                    }
                }
            }

            public override string ToString()
            {
                switch (SlewRate)
                {
                    case CyRate.Fast:
                        return "Fast";

                    case CyRate.Slow:
                        return "Slow";

                    default:
                        Debug.Fail("unhandled");
                        return base.ToString();
                }
            }
        }

        class CyDriveLevel
        {
            public enum CyLevel { Vddio, Vref };

            CyLevel m_level;

            public CyLevel DriveLevel { get { return m_level; } }

            public CyDriveLevel(CyLevel level)
            {
                m_level = level;
            }

            public string ParamValue
            {
                get
                {
                    switch (DriveLevel)
                    {
                        case CyLevel.Vddio:
                            return CyPortConstants.OutputDriveLevelValue_VDDIO;

                        case CyLevel.Vref:
                            return CyPortConstants.OutputDriveLevelValue_VREF;

                        default:
                            Debug.Fail("unhandled");
                            return string.Empty;
                    }
                }
            }

            public override string ToString()
            {
                switch (DriveLevel)
                {
                    case CyLevel.Vddio:
                        return "Vddio";

                    case CyLevel.Vref:
                        return "Vref";

                    default:
                        Debug.Fail("unhandled");
                        return base.ToString();
                }
            }
        }

        class CyDriveCurrent
        {
            public enum CyCurrent { Source4Sink8, Source4Sink25 };

            CyCurrent m_current;

            public CyCurrent DriveCurrent { get { return m_current; } }

            public CyDriveCurrent(CyCurrent current)
            {
                m_current = current;
            }

            public string ParamValue
            {
                get
                {
                    switch (DriveCurrent)
                    {
                        case CyCurrent.Source4Sink25:
                            return CyPortConstants.DriveCurrentValue_4SOURCE_25SINK;

                        case CyCurrent.Source4Sink8:
                            return CyPortConstants.DriveCurrentValue_4SOURCE_8SINK;

                        default:
                            Debug.Fail("unhandled");
                            return string.Empty;
                    }
                }
            }

            public override string ToString()
            {
                switch (DriveCurrent)
                {
                    case CyCurrent.Source4Sink25:
                        return "4mA source, 25mA sink";

                    case CyCurrent.Source4Sink8:
                        return "4mA source, 8mA sink";

                    default:
                        Debug.Fail("unhandled");
                        return base.ToString();
                }
            }
        }

        class CyOutputMode
        {
            public enum CyOutMode { Transparent, SingleSync, ClockNormal, ClockInverted };

            CyOutMode m_outMode;

            public CyOutMode OutMode { get { return m_outMode; } }

            public CyOutputMode(CyOutMode outMode)
            {
                m_outMode = outMode;
            }

            public override string ToString()
            {
                switch (OutMode)
                {
                    case CyOutMode.Transparent:
                        return "Transparent";

                    case CyOutMode.SingleSync:
                        return "Single-Sync";

                    case CyOutMode.ClockNormal:
                        return "Clock";

                    case CyOutMode.ClockInverted:
                        return "Clock-Inverted";

                    default:
                        Debug.Fail("unhandled");
                        return base.ToString();
                }
            }
        }
    }
}
