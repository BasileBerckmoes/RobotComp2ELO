/*******************************************************************************
* Copyright 2008-2014, Cypress Semiconductor Corporation.  All rights reserved.
* You may use this file only in accordance with the license, terms, conditions, 
* disclaimers, and limitations in the end user license agreement accompanying 
* the software package with which this file was provided.
********************************************************************************/

using System;
using System.Collections.Generic;
using System.Windows.Forms;

namespace Cypress.Comps.PinsAndPorts.cy_pins_v2_10
{
    public partial class CyOutputControl : UserControl
    {
        public static readonly CyPinData.ErrorMgrKey[] OwnedSettings = new CyPinData.ErrorMgrKey[]
        {
            CyPinData.ErrorMgrKey.OUTPUT_ENABLE_SYNCHRONIZED,
            CyPinData.ErrorMgrKey.OUTPUT_SLEW_RATE,
            CyPinData.ErrorMgrKey.OUTPUT_DRIVE_LEVEL,
            CyPinData.ErrorMgrKey.OUTPUT_CURRENT,
            CyPinData.ErrorMgrKey.OUTPUT_MODE,
        };

        private IList<CyPinData.PerPin> m_pins;
        private CyPerPinDataControl.SIOStateChangedHandler m_onSIOStateChanged;

        public CyOutputControl(CyDeviceSupport deviceSupport, CyErrorManager errMgr, CyPinData pins, 
            CyPerPinDataControl.SIOStateChangedHandler sioStateChanged, bool isSysBuilder)
        {
            InitializeComponent();

            m_onSIOStateChanged = sioStateChanged;
            bool show25MaSink = !deviceSupport.HasData || deviceSupport.HasSIO;
            bool show10MaSink = !deviceSupport.HasData || (deviceSupport.IsPSoC4 && (deviceSupport.HasOVT || deviceSupport.HasSIO));
            bool showOutModeClk = !deviceSupport.HasData || deviceSupport.HasPortAdapter;
            bool showOutModeSync = !deviceSupport.HasData || deviceSupport.HasPortAdapter || deviceSupport.IsPSoC3 || deviceSupport.IsPSoC5;
            bool showOeSink = !deviceSupport.HasData || deviceSupport.HasPortAdapter;
            bool showOutLevelVref = !deviceSupport.HasData || deviceSupport.HasSIO;
            bool showI2CSlewRates = !deviceSupport.HasData || deviceSupport.HasOVT;
            foreach (CyPinData.PerPin pin in pins.Pins)
            {
                show25MaSink |= (pin.OutputCurrent == CyOutputCurrent.SOURCE_4MA_SINK_25MA);
                show10MaSink |= (pin.OutputCurrent == CyOutputCurrent.SOURCE_4MA_SINK_10MA);
                showOutModeClk |= (pin.OutputMode == CyOutputMode.CLOCK || pin.OutputMode == CyOutputMode.CLOCK_INV);
                showOutModeSync |= (pin.OutputMode == CyOutputMode.SINGLE_SYNC);
                showOeSink |= pin.OutputEnableSynchronized;
                showOutLevelVref |= (pin.OutputDriveLevel != CyOutputDriveLevel.VDDIO);
                showI2CSlewRates |= CyPinData.PerPin.RequiresOvt(pin.OutputSlewRate);
            }

            m_slewRateComboBox.DropDownStyle = ComboBoxStyle.DropDownList;
            m_slewRateComboBox.Items.Add(new CyComboItem<CyOutputSlewRate>(CyOutputSlewRate.SLOW, "Slow"));
            m_slewRateComboBox.Items.Add(new CyComboItem<CyOutputSlewRate>(CyOutputSlewRate.FAST, "Fast"));
            if (showI2CSlewRates)
            {
                m_slewRateComboBox.Items.Add(new CyComboItem<CyOutputSlewRate>(CyOutputSlewRate.I2CFM, "I2C FM+"));
                // TODO: Re-enable when the BROS is updated with the conclusions from CDT 186940
                //m_slewRateComboBox.Items.Add(new CyComboItem<CyOutputSlewRate>(CyOutputSlewRate.I2CHS, "I2C HS (3.4 Mbps)"));
            }

            m_driveLevelComboBox.DropDownStyle = ComboBoxStyle.DropDownList;
            m_driveLevelComboBox.Items.Add(new CyComboItem<CyOutputDriveLevel>(CyOutputDriveLevel.VDDIO, "Vddio"));
            if (showOutLevelVref)
                m_driveLevelComboBox.Items.Add(new CyComboItem<CyOutputDriveLevel>(CyOutputDriveLevel.VREF, "Vref"));

            m_currentComboBox.DropDownStyle = ComboBoxStyle.DropDownList;
            m_currentComboBox.Items.Add(
                new CyComboItem<CyOutputCurrent>(CyOutputCurrent.SOURCE_4MA_SINK_8MA, "4mA source, 8mA sink"));
            if (show10MaSink)
            {
                m_currentComboBox.Items.Add(
                    new CyComboItem<CyOutputCurrent>(CyOutputCurrent.SOURCE_4MA_SINK_10MA, "4mA source, 10mA sink"));
            }
            if (show25MaSink)
            {
                m_currentComboBox.Items.Add(
                    new CyComboItem<CyOutputCurrent>(CyOutputCurrent.SOURCE_4MA_SINK_25MA, "4mA source, 25mA sink"));
            }

            m_outputModeComboBox.DropDownStyle = ComboBoxStyle.DropDownList;
            m_outputModeComboBox.Items.Add(new CyComboItem<CyOutputMode>(CyOutputMode.TRANSPARENT, "Transparent"));
            if (showOutModeSync)
            {
                m_outputModeComboBox.Items.Add(new CyComboItem<CyOutputMode>(CyOutputMode.SINGLE_SYNC, "Single-Sync"));
            }
            if (showOutModeClk)
            {
                m_outputModeComboBox.Items.Add(new CyComboItem<CyOutputMode>(CyOutputMode.CLOCK, "Clock"));
                m_outputModeComboBox.Items.Add(new CyComboItem<CyOutputMode>(CyOutputMode.CLOCK_INV, "Clock-Inverted"));
            }

            m_oeSyncCheckBox.Visible = showOeSink;

            if (isSysBuilder)
            {
                m_oeSyncCheckBox.Visible = false;
            }

            EnableEvents();

            m_errorProvider.SetIconAlignment(m_slewRateComboBox, ErrorIconAlignment.MiddleLeft);
            m_errorProvider.SetIconPadding(m_slewRateComboBox, 3);
            m_errorProvider.SetIconAlignment(m_driveLevelComboBox, ErrorIconAlignment.MiddleLeft);
            m_errorProvider.SetIconPadding(m_driveLevelComboBox, 3);
            m_errorProvider.SetIconAlignment(m_currentComboBox, ErrorIconAlignment.MiddleLeft);
            m_errorProvider.SetIconPadding(m_currentComboBox, 3);
            m_errorProvider.SetIconAlignment(m_oeSyncCheckBox, ErrorIconAlignment.MiddleLeft);
            m_errorProvider.SetIconPadding(m_oeSyncCheckBox, 3);

            errMgr.RegisterSettingOwner(CyPinData.ErrorMgrKey.OUTPUT_ENABLE_SYNCHRONIZED, m_errorProvider, m_oeSyncCheckBox);
            errMgr.RegisterSettingOwner(CyPinData.ErrorMgrKey.OUTPUT_SLEW_RATE, m_errorProvider, m_slewRateComboBox);
            errMgr.RegisterSettingOwner(CyPinData.ErrorMgrKey.OUTPUT_DRIVE_LEVEL, m_errorProvider, m_driveLevelComboBox);
            errMgr.RegisterSettingOwner(CyPinData.ErrorMgrKey.OUTPUT_CURRENT, m_errorProvider, m_currentComboBox);
            errMgr.RegisterSettingOwner(CyPinData.ErrorMgrKey.OUTPUT_MODE, m_errorProvider, m_outputModeComboBox);
        }

        private void EnableEvents()
        {
            m_oeSyncCheckBox.CheckedChanged += m_oeSyncCheckBox_CheckedChanged;
            m_slewRateComboBox.SelectedIndexChanged += m_slewRateComboBox_SelectedIndexChanged;
            m_driveLevelComboBox.SelectedIndexChanged += m_driveLevelComboBox_SelectedIndexChanged;
            m_currentComboBox.SelectedIndexChanged += m_currentComboBox_SelectedIndexChanged;
            m_outputModeComboBox.SelectedIndexChanged += m_outputModeComboBox_SelectedIndexChanged;
        }
        private void DisableEvents()
        {
            m_oeSyncCheckBox.CheckedChanged -= m_oeSyncCheckBox_CheckedChanged;
            m_slewRateComboBox.SelectedIndexChanged -= m_slewRateComboBox_SelectedIndexChanged;
            m_driveLevelComboBox.SelectedIndexChanged -= m_driveLevelComboBox_SelectedIndexChanged;
            m_currentComboBox.SelectedIndexChanged -= m_currentComboBox_SelectedIndexChanged;
            m_outputModeComboBox.SelectedIndexChanged -= m_outputModeComboBox_SelectedIndexChanged;
        }

        internal void UpdateData()
        {
            CheckState oeSync = m_pins[0].OutputEnableSynchronized ? CheckState.Checked : CheckState.Unchecked;
            int slew = Utils.GetIndex<CyOutputSlewRate>(m_slewRateComboBox, m_pins[0].OutputSlewRate);
            int level = Utils.GetIndex<CyOutputDriveLevel>(m_driveLevelComboBox, m_pins[0].OutputDriveLevel);
            int current = Utils.GetIndex<CyOutputCurrent>(m_currentComboBox, m_pins[0].OutputCurrent);
            int mode = Utils.GetIndex<CyOutputMode>(m_outputModeComboBox, m_pins[0].OutputMode);

            for (int i = 1; i < m_pins.Count; i++)
            {
                if (oeSync != (m_pins[i].OutputEnableSynchronized ? CheckState.Checked : CheckState.Unchecked))
                    oeSync = CheckState.Indeterminate;

                if (slew != (Utils.GetIndex<CyOutputSlewRate>(m_slewRateComboBox, m_pins[i].OutputSlewRate)))
                    slew = -1;
                if (level != (Utils.GetIndex<CyOutputDriveLevel>(m_driveLevelComboBox, m_pins[i].OutputDriveLevel)))
                    level = -1;
                if (current != (Utils.GetIndex<CyOutputCurrent>(m_currentComboBox, m_pins[i].OutputCurrent)))
                    current = -1;
                if (mode != (Utils.GetIndex<CyOutputMode>(m_outputModeComboBox, m_pins[i].OutputMode)))
                    mode = -1;
            }

            DisableEvents();

            m_oeSyncCheckBox.CheckState = oeSync;
            m_slewRateComboBox.SelectedIndex = slew;
            m_driveLevelComboBox.SelectedIndex = level;
            m_currentComboBox.SelectedIndex = current;
            m_outputModeComboBox.SelectedIndex = mode;

            EnableEvents();
        }

        internal void UpdateData(IList<CyPinData.PerPin> pins)
        {
            m_pins = pins;
            UpdateData();
        }

        void m_currentComboBox_SelectedIndexChanged(object sender, EventArgs e)
        {
            foreach (CyPinData.PerPin pin in m_pins)
                pin.OutputCurrent = ((CyComboItem<CyOutputCurrent>)m_currentComboBox.SelectedItem).Item;
            m_onSIOStateChanged(); // Current can impact "SIO-ness"
        }

        void m_driveLevelComboBox_SelectedIndexChanged(object sender, EventArgs e)
        {
            foreach (CyPinData.PerPin pin in m_pins)
                pin.OutputDriveLevel = ((CyComboItem<CyOutputDriveLevel>)m_driveLevelComboBox.SelectedItem).Item;
            m_onSIOStateChanged(); // Drive level can impact "SIO-ness"
        }

        void m_outputModeComboBox_SelectedIndexChanged(object sender, EventArgs e)
        {
            foreach (CyPinData.PerPin pin in m_pins)
                pin.OutputMode = ((CyComboItem<CyOutputMode>)m_outputModeComboBox.SelectedItem).Item;
        }

        void m_oeSyncCheckBox_CheckedChanged(object sender, EventArgs e)
        {
            foreach (CyPinData.PerPin pin in m_pins)
                pin.OutputEnableSynchronized = m_oeSyncCheckBox.Checked;
        }

        void m_slewRateComboBox_SelectedIndexChanged(object sender, EventArgs e)
        {
            foreach (CyPinData.PerPin pin in m_pins)
                pin.OutputSlewRate = ((CyComboItem<CyOutputSlewRate>)m_slewRateComboBox.SelectedItem).Item;
        }
    }
}
