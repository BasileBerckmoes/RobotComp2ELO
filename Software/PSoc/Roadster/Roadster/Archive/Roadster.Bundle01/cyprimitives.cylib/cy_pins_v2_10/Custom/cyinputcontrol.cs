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
    public partial class CyInputControl : UserControl
    {
        public static readonly CyPinData.ErrorMgrKey[] OwnedSettings = new CyPinData.ErrorMgrKey[]
        {
            CyPinData.ErrorMgrKey.INPUT_HOT_SWAP,
            CyPinData.ErrorMgrKey.INPUT_BUFFER_ENABLED,
            CyPinData.ErrorMgrKey.INPUT_SYNC_MODE,
            CyPinData.ErrorMgrKey.INPUT_INTERRUPT,
            CyPinData.ErrorMgrKey.INPUT_THRESHOLD,
            CyPinData.ErrorMgrKey.INPUT_HYSTERESIS,
        };

        private IList<CyPinData.PerPin> m_pins;
        private CyPerPinDataControl.SIOStateChangedHandler m_onSIOStateChanged;
        private readonly CyDeviceSupport m_deviceSupport;
        
        public CyInputControl(CyDeviceSupport deviceSupport, CyErrorManager errMgr, CyPinData pins, 
            CyPerPinDataControl.SIOStateChangedHandler onSioStateChanged)
        {
            InitializeComponent();
            m_onSIOStateChanged = onSioStateChanged;
            m_deviceSupport = deviceSupport;
            bool showSioThreshold = !deviceSupport.HasData || deviceSupport.HasSIO;
            // CMOS 1.8V is available on all devices with GPIOv2 or later. 
            bool showCmosThreshold = !deviceSupport.HasData || deviceSupport.GPIOVersion > 1;
            bool showSingleSync = !deviceSupport.HasData || deviceSupport.HasPortAdapter;
            bool showDblSync = (!deviceSupport.HasData || deviceSupport.IsPSoC3 || deviceSupport.IsPSoC5 || deviceSupport.HasPortAdapter);
            foreach (CyPinData.PerPin pin in pins.Pins)
            {
                showSioThreshold |= CyPinData.PerPin.RequiresSio(pin.InputThreshold);
                showSingleSync |= (pin.InputSyncMode == CyInputSyncMode.SINGLE_SYNC);
                showDblSync |= (pin.InputSyncMode == CyInputSyncMode.DOUBLE_SYNC);
                showCmosThreshold |= (pin.InputThreshold == CyInputThreshold.CMOS_1PT8V);
            }

            m_inputBufferEnabledCheckBox.Enabled = !deviceSupport.IsTSG4;

            m_thresholdComboBox.DropDownStyle = ComboBoxStyle.DropDownList;
            m_thresholdComboBox.Items.Add(
                new CyComboItem<CyInputThreshold>(CyInputThreshold.CMOS, "CMOS"));
            m_thresholdComboBox.Items.Add(
                new CyComboItem<CyInputThreshold>(CyInputThreshold.CMOS_LVTTL, "CMOS or LVTTL"));
            m_thresholdComboBox.Items.Add(
                new CyComboItem<CyInputThreshold>(CyInputThreshold.LVTTL, "LVTTL"));
            if (showSioThreshold)
            {
                m_thresholdComboBox.Items.Add(
                    new CyComboItem<CyInputThreshold>(CyInputThreshold.PT4_VDDIO, "0.4 x Vddio"));
                m_thresholdComboBox.Items.Add(
                    new CyComboItem<CyInputThreshold>(CyInputThreshold.PT5_VDDIO, "0.5 x Vddio"));
                m_thresholdComboBox.Items.Add(
                    new CyComboItem<CyInputThreshold>(CyInputThreshold.PT5_VREF, "0.5 x Vref"));
                m_thresholdComboBox.Items.Add(
                    new CyComboItem<CyInputThreshold>(CyInputThreshold.VREF, "Vref"));
            }
            if (showCmosThreshold)
            {
                m_thresholdComboBox.Items.Add(
                    new CyComboItem<CyInputThreshold>(CyInputThreshold.CMOS_1PT8V, "CMOS 1.8V"));
            }

            m_interruptComboBox.DropDownStyle = ComboBoxStyle.DropDownList;
            m_interruptComboBox.Items.Add(
                new CyComboItem<CyInputInterruptTrigger>(CyInputInterruptTrigger.NONE, "None"));
            m_interruptComboBox.Items.Add(
                new CyComboItem<CyInputInterruptTrigger>(CyInputInterruptTrigger.RISING_EDGE, "Rising edge"));
            m_interruptComboBox.Items.Add(
                new CyComboItem<CyInputInterruptTrigger>(CyInputInterruptTrigger.FALLING_EDGE, "Falling edge"));
            m_interruptComboBox.Items.Add(
                new CyComboItem<CyInputInterruptTrigger>(CyInputInterruptTrigger.BOTH_EDGES, "Both edges"));

            m_inputSyncComboBox.DropDownStyle = ComboBoxStyle.DropDownList;
            if (showDblSync)
            {
                m_inputSyncComboBox.Items.Add(
                    new CyComboItem<CyInputSyncMode>(CyInputSyncMode.DOUBLE_SYNC, "Double-sync"));
            }
            if (showSingleSync)
            {
                m_inputSyncComboBox.Items.Add(
                    new CyComboItem<CyInputSyncMode>(CyInputSyncMode.SINGLE_SYNC, "Single-sync"));
            }
            m_inputSyncComboBox.Items.Add(new CyComboItem<CyInputSyncMode>(CyInputSyncMode.TRANSPARENT, "Transparent"));

            EnableEvents();

            m_errorProvider.SetIconAlignment(m_inputBufferEnabledCheckBox, ErrorIconAlignment.MiddleLeft);
            m_errorProvider.SetIconPadding(m_inputBufferEnabledCheckBox, 3);
            m_errorProvider.SetIconAlignment(m_inputSyncComboBox, ErrorIconAlignment.MiddleRight);
            m_errorProvider.SetIconPadding(m_inputSyncComboBox, 3);
            m_errorProvider.SetIconAlignment(m_interruptComboBox, ErrorIconAlignment.MiddleLeft);
            m_errorProvider.SetIconPadding(m_interruptComboBox, 3);
            m_errorProvider.SetIconAlignment(m_thresholdComboBox, ErrorIconAlignment.MiddleLeft);
            m_errorProvider.SetIconPadding(m_thresholdComboBox, 3);

            errMgr.RegisterSettingOwner(CyPinData.ErrorMgrKey.INPUT_BUFFER_ENABLED, m_errorProvider, m_inputBufferEnabledCheckBox);
            errMgr.RegisterSettingOwner(CyPinData.ErrorMgrKey.INPUT_SYNC_MODE, m_errorProvider, m_inputSyncComboBox);
            errMgr.RegisterSettingOwner(CyPinData.ErrorMgrKey.INPUT_INTERRUPT, m_errorProvider, m_interruptComboBox);
            errMgr.RegisterSettingOwner(CyPinData.ErrorMgrKey.INPUT_THRESHOLD, m_errorProvider, m_thresholdComboBox);
            errMgr.RegisterSettingOwner(CyPinData.ErrorMgrKey.INPUT_HYSTERESIS, m_errorProvider, m_hysteresisCheckBox);
        }

        private void UpdateHysteresisDisplay(IEnumerable<CyPinData.PerPin> pins)
        {
            // SIO Hysteresis off option is only enabled if all selected pins use an SIO-specific threshold
            bool hysteresisConfigurable = true; 
            // Assume hysteresis is configurable, since we break as soon as we find one which is not. We always
            // have at least one pin so we don't have to worry about having a false positive
            foreach (CyPinData.PerPin pin in pins)
            {
                if (!CyPinData.PerPin.RequiresSio(pin.InputThreshold))
                {
                    hysteresisConfigurable = false;
                    break;
                }
            }

            // When the hysteresis checkbox first becomes available, we want it to default to false - but we 
            // don't want to force it back to false every time they change between SIO settings
            if (!m_hysteresisCheckBox.Enabled && hysteresisConfigurable)
                m_hysteresisCheckBox.Checked = false;
            else if (!hysteresisConfigurable)
                m_hysteresisCheckBox.Checked = true; // Hysteresis is always on for standard GPIOs

            m_hysteresisCheckBox.Enabled = hysteresisConfigurable;
        }

        private void EnableEvents()
        {
            m_inputBufferEnabledCheckBox.CheckedChanged += m_inputBufferEnabledCheckBox_CheckedChanged;
            m_inputSyncComboBox.SelectedIndexChanged += m_inputSyncComboBox_SelectedIndexChanged;
            m_interruptComboBox.SelectedIndexChanged += m_interruptComboBox_SelectedIndexChanged;
            m_thresholdComboBox.SelectedIndexChanged += m_thresholdComboBox_SelectedIndexChanged;
            m_hysteresisCheckBox.CheckedChanged += m_hysteresisCheckBox_CheckedChanged;
        }
        private void DisableEvents()
        {
            m_inputBufferEnabledCheckBox.CheckedChanged -= m_inputBufferEnabledCheckBox_CheckedChanged;
            m_inputSyncComboBox.SelectedIndexChanged -= m_inputSyncComboBox_SelectedIndexChanged;
            m_interruptComboBox.SelectedIndexChanged -= m_interruptComboBox_SelectedIndexChanged;
            m_thresholdComboBox.SelectedIndexChanged -= m_thresholdComboBox_SelectedIndexChanged;
            m_hysteresisCheckBox.CheckedChanged -= m_hysteresisCheckBox_CheckedChanged;
        }

        internal void UpdateData()
        {
            DisableEvents();

            UpdateHysteresisDisplay(m_pins);

            CheckState inputBuffer = m_pins[0].InputBufferEnabled ? CheckState.Checked : CheckState.Unchecked;
            CheckState hysteresis = m_pins[0].InputHysteresis ? CheckState.Checked :  CheckState.Unchecked;
            int threshold = Utils.GetIndex(m_thresholdComboBox, m_pins[0].InputThreshold);
            int interrupt = Utils.GetIndex(m_interruptComboBox, m_pins[0].InputInterrupt);
            int sync = Utils.GetIndex(m_inputSyncComboBox, m_pins[0].InputSyncMode);

            for (int i = 1; i < m_pins.Count; i++)
            {
                if (inputBuffer != (m_pins[i].InputBufferEnabled ? CheckState.Checked : CheckState.Unchecked))
                    inputBuffer = CheckState.Indeterminate;
                if (hysteresis != (m_pins[i].InputHysteresis ? CheckState.Checked : CheckState.Unchecked))
                    hysteresis = CheckState.Indeterminate;
                if (threshold != (Utils.GetIndex<CyInputThreshold>(m_thresholdComboBox, m_pins[i].InputThreshold)))
                    threshold = -1;
                if (interrupt != (Utils.GetIndex<CyInputInterruptTrigger>(m_interruptComboBox, m_pins[i].InputInterrupt)))
                    interrupt = -1;
                if (sync != (Utils.GetIndex<CyInputSyncMode>(m_inputSyncComboBox, m_pins[i].InputSyncMode)))
                    sync = -1;
            }


            m_hysteresisCheckBox.CheckState = hysteresis;
            m_inputBufferEnabledCheckBox.CheckState = inputBuffer;
            m_thresholdComboBox.SelectedIndex = threshold;
            m_interruptComboBox.SelectedIndex = interrupt;
            m_inputSyncComboBox.SelectedIndex = sync;

            EnableEvents();
        }

        internal void UpdateData(IList<CyPinData.PerPin> pins)
        {
            m_pins = pins;
            UpdateData();
        }

        private void m_thresholdComboBox_SelectedIndexChanged(object sender, EventArgs e)
        {
            CyInputThreshold newThreshold = 
                ((CyComboItem<CyInputThreshold>)m_thresholdComboBox.SelectedItem).Item;

            foreach (CyPinData.PerPin pin in m_pins)
                pin.InputThreshold = newThreshold;

            UpdateHysteresisDisplay(m_pins);

            // Threshold can impact SIO status - make sure the list is updated to reflect this
            m_onSIOStateChanged();
        }

        private void m_interruptComboBox_SelectedIndexChanged(object sender, EventArgs e)
        {
            CyInputInterruptTrigger trigger = ((CyComboItem<CyInputInterruptTrigger>)m_interruptComboBox.SelectedItem).Item;
            foreach (CyPinData.PerPin pin in m_pins)
                pin.InputInterrupt = trigger;
        }

        private void m_inputSyncComboBox_SelectedIndexChanged(object sender, EventArgs e)
        {
            foreach (CyPinData.PerPin pin in m_pins)
                pin.InputSyncMode = ((CyComboItem<CyInputSyncMode>)m_inputSyncComboBox.SelectedItem).Item;
        }

        private void m_inputBufferEnabledCheckBox_CheckedChanged(object sender, EventArgs e)
        {
            foreach (CyPinData.PerPin pin in m_pins)
                pin.InputBufferEnabled = m_inputBufferEnabledCheckBox.Checked;
        }

        private void m_hysteresisCheckBox_CheckedChanged(object sender, EventArgs e)
        {
            foreach (CyPinData.PerPin pin in m_pins)
                pin.InputHysteresis = m_hysteresisCheckBox.Checked;
        }
    }
}
