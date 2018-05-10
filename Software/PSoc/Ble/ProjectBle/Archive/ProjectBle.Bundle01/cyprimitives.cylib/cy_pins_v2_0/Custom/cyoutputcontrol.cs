/*******************************************************************************
* Copyright 2008-2013, Cypress Semiconductor Corporation.  All rights reserved.
* You may use this file only in accordance with the license, terms, conditions, 
* disclaimers, and limitations in the end user license agreement accompanying 
* the software package with which this file was provided.
********************************************************************************/

using System;
using System.Collections.Generic;
using System.Diagnostics;
using System.Windows.Forms;
using CyDesigner.Extensions.Gde;

namespace Cypress.Comps.PinsAndPorts.cy_pins_v2_0
{
    public partial class CyOutputControl : UserControl
    {
        public static readonly CyPinData.Key[] OwnedSettings = new CyPinData.Key[]
        {
            CyPinData.Key.OUTPUT_ENABLE_SYNCHRONIZED,
            CyPinData.Key.OUTPUT_SLEW_RATE,
            CyPinData.Key.OUTPUT_DRIVE_LEVEL,
            CyPinData.Key.OUTPUT_CURRENT,
            CyPinData.Key.OUTPUT_MODE,
        };

        private IList<CyPinData.PerPin> m_pins;
        private CyPerPinDataControl.SIOStateChangedHandler m_onSIOStateChanged;

        public CyOutputControl(CyDeviceSupport deviceSupport, CyErrorManager errMgr, CyPinData pins, CyPerPinDataControl.SIOStateChangedHandler sioStateChanged)
        {
            InitializeComponent();

            m_onSIOStateChanged = sioStateChanged;
            bool show25MaSink = !deviceSupport.HasData || deviceSupport.HasSIO;
            bool showOutModeClk = !deviceSupport.HasData || deviceSupport.HasPortAdapter;
            bool showOeSink = !deviceSupport.HasData || deviceSupport.IsPSoC4;
            bool showOutLevelVref = !deviceSupport.HasData || deviceSupport.HasSIO;
            foreach (CyPinData.PerPin pin in pins.Pins)
            {
                show25MaSink |= (pin.OutputCurrent == CyOutputCurrent.SOURCE_4MA_SINK_25MA);
                showOutModeClk |= (pin.OutputMode == CyOutputMode.CLOCK || pin.OutputMode == CyOutputMode.CLOCK_INV);
                showOeSink |= pin.OutputEnableSynchronized;
                showOutLevelVref |= (pin.OutputDriveLevel != CyOutputDriveLevel.VDDIO);
            }

            m_slewRateComboBox.DropDownStyle = ComboBoxStyle.DropDownList;
            m_slewRateComboBox.Items.Add(new CyComboItem<CyOutputSlewRate>(CyOutputSlewRate.SLOW, "Slow"));
            m_slewRateComboBox.Items.Add(new CyComboItem<CyOutputSlewRate>(CyOutputSlewRate.FAST, "Fast"));

            m_driveLevelComboBox.DropDownStyle = ComboBoxStyle.DropDownList;
            m_driveLevelComboBox.Items.Add(new CyComboItem<CyOutputDriveLevel>(CyOutputDriveLevel.VDDIO, "Vddio"));
            if (showOutLevelVref)
                m_driveLevelComboBox.Items.Add(new CyComboItem<CyOutputDriveLevel>(CyOutputDriveLevel.VREF, "Vref"));

            m_currentComboBox.DropDownStyle = ComboBoxStyle.DropDownList;
            m_currentComboBox.Items.Add(
                new CyComboItem<CyOutputCurrent>(CyOutputCurrent.SOURCE_4MA_SINK_8MA, "4mA source, 8mA sink"));
            if (show25MaSink)
            {
                m_currentComboBox.Items.Add(
                    new CyComboItem<CyOutputCurrent>(CyOutputCurrent.SOURCE_4MA_SINK_25MA, "4mA source, 25mA sink"));
            }

            m_outputModeComboBox.DropDownStyle = ComboBoxStyle.DropDownList;
            m_outputModeComboBox.Items.Add(new CyComboItem<CyOutputMode>(CyOutputMode.TRANSPARENT, "Transparent"));
            m_outputModeComboBox.Items.Add(new CyComboItem<CyOutputMode>(CyOutputMode.SINGLE_SYNC, "Single-Sync"));
            if (showOutModeClk)
            {
                m_outputModeComboBox.Items.Add(new CyComboItem<CyOutputMode>(CyOutputMode.CLOCK, "Clock"));
                m_outputModeComboBox.Items.Add(new CyComboItem<CyOutputMode>(CyOutputMode.CLOCK_INV, "Clock-Inverted"));
            }

            m_oeSyncCheckBox.Visible = showOeSink;

            EnableEvents();

            m_errorProvider.SetIconAlignment(m_slewRateComboBox, ErrorIconAlignment.MiddleLeft);
            m_errorProvider.SetIconPadding(m_slewRateComboBox, 3);
            m_errorProvider.SetIconAlignment(m_driveLevelComboBox, ErrorIconAlignment.MiddleLeft);
            m_errorProvider.SetIconPadding(m_driveLevelComboBox, 3);
            m_errorProvider.SetIconAlignment(m_currentComboBox, ErrorIconAlignment.MiddleLeft);
            m_errorProvider.SetIconPadding(m_currentComboBox, 3);
            m_errorProvider.SetIconAlignment(m_oeSyncCheckBox, ErrorIconAlignment.MiddleLeft);
            m_errorProvider.SetIconPadding(m_oeSyncCheckBox, 3);

            errMgr.RegisterSettingOwner(CyPinData.Key.OUTPUT_ENABLE_SYNCHRONIZED, m_errorProvider, m_oeSyncCheckBox);
            errMgr.RegisterSettingOwner(CyPinData.Key.OUTPUT_SLEW_RATE, m_errorProvider, m_slewRateComboBox);
            errMgr.RegisterSettingOwner(CyPinData.Key.OUTPUT_DRIVE_LEVEL, m_errorProvider, m_driveLevelComboBox);
            errMgr.RegisterSettingOwner(CyPinData.Key.OUTPUT_CURRENT, m_errorProvider, m_currentComboBox);
            errMgr.RegisterSettingOwner(CyPinData.Key.OUTPUT_MODE, m_errorProvider, m_outputModeComboBox);
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

        internal void UpdateData(IList<CyPinData.PerPin> pins)
        {
            m_pins = pins;

            CheckState oeSync = pins[0].OutputEnableSynchronized ? CheckState.Checked : CheckState.Unchecked;
            int slew = Utils.GetIndex<CyOutputSlewRate>(m_slewRateComboBox, pins[0].OutputSlewRate);
            int level = Utils.GetIndex<CyOutputDriveLevel>(m_driveLevelComboBox, pins[0].OutputDriveLevel);
            int current = Utils.GetIndex<CyOutputCurrent>(m_currentComboBox, pins[0].OutputCurrent);
            int mode = Utils.GetIndex<CyOutputMode>(m_outputModeComboBox, pins[0].OutputMode);

            for (int i = 1; i < pins.Count; i++)
            {
                if (oeSync != (pins[i].OutputEnableSynchronized ? CheckState.Checked : CheckState.Unchecked))
                    oeSync = CheckState.Indeterminate;

                if (slew != (Utils.GetIndex<CyOutputSlewRate>(m_slewRateComboBox, pins[i].OutputSlewRate)))
                    slew = -1;
                if (level != (Utils.GetIndex<CyOutputDriveLevel>(m_driveLevelComboBox, pins[i].OutputDriveLevel)))
                    level = -1;
                if (current != (Utils.GetIndex<CyOutputCurrent>(m_currentComboBox, pins[i].OutputCurrent)))
                    current = -1;
                if (mode != (Utils.GetIndex<CyOutputMode>(m_outputModeComboBox, pins[i].OutputMode)))
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
