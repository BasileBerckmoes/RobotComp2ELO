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
    public partial class CyInputControl : UserControl
    {
        public static readonly CyPinData.Key[] OwnedSettings = new CyPinData.Key[]
        {
            CyPinData.Key.INPUT_HOT_SWAP,
            CyPinData.Key.INPUT_BUFFER_ENABLED,
            CyPinData.Key.INPUT_SYNC_MODE,
            CyPinData.Key.INPUT_INTERRUPT,
            CyPinData.Key.INPUT_THRESHOLD,
            CyPinData.Key.INPUT_HYSTERESIS,
        };

        private IList<CyPinData.PerPin> m_pins;
        private CyPerPinDataControl.SIOStateChangedHandler m_onSIOStateChanged;
        
        public CyInputControl(CyDeviceSupport deviceSupport, CyErrorManager errMgr, CyPinData pins, CyPerPinDataControl.SIOStateChangedHandler onSioStateChanged)
        {
            InitializeComponent();
            m_onSIOStateChanged = onSioStateChanged;
            bool showHotSwap = !deviceSupport.HasData || deviceSupport.HasSIO;
            bool showSioThreshold = !deviceSupport.HasData || deviceSupport.HasSIO;
            bool showSingleSync = !deviceSupport.HasData || deviceSupport.HasPortAdapter;
            bool showDblSync = (!deviceSupport.HasData || deviceSupport.IsPSoC3 || deviceSupport.IsPSoC5 || deviceSupport.HasPortAdapter);
            foreach (CyPinData.PerPin pin in pins.Pins)
            {
                showHotSwap |= pin.InputHotSwap;
                showSioThreshold |= CanToggleHysteresis(pin.InputThreshold);
                showSingleSync |= (pin.InputSyncMode == CyInputSyncMode.SINGLE_SYNC);
                showDblSync |= (pin.InputSyncMode == CyInputSyncMode.DOUBLE_SYNC);
            }

            m_hotSwapCheckBox.Visible = showHotSwap;
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
            m_hysteresisCheckBox.Enabled = showSioThreshold; // GPIOs have hysteresis always enabled

            m_interruptComboBox.DropDownStyle = ComboBoxStyle.DropDownList;
            m_interruptComboBox.Items.Add(
                new CyComboItem<CyInputInterruptTrigger>(CyInputInterruptTrigger.NONE, "None"));
            m_interruptComboBox.Items.Add(
                new CyComboItem<CyInputInterruptTrigger>(CyInputInterruptTrigger.RISING_EDGE, "Rising Edge"));
            m_interruptComboBox.Items.Add(
                new CyComboItem<CyInputInterruptTrigger>(CyInputInterruptTrigger.FALLING_EDGE, "Falling Edge"));
            m_interruptComboBox.Items.Add(
                new CyComboItem<CyInputInterruptTrigger>(CyInputInterruptTrigger.BOTH_EDGES, "Both Edges"));

            m_inputSyncComboBox.DropDownStyle = ComboBoxStyle.DropDownList;
            if (showDblSync)
            {
                m_inputSyncComboBox.Items.Add(
                    new CyComboItem<CyInputSyncMode>(CyInputSyncMode.DOUBLE_SYNC, "Double-Sync"));
            }
            if (showSingleSync)
            {
                m_inputSyncComboBox.Items.Add(
                    new CyComboItem<CyInputSyncMode>(CyInputSyncMode.SINGLE_SYNC, "Single-Sync"));
            }
            m_inputSyncComboBox.Items.Add(new CyComboItem<CyInputSyncMode>(CyInputSyncMode.TRANSPARENT, "Transparent"));

            EnableEvents();

            m_errorProvider.SetIconAlignment(m_hotSwapCheckBox, ErrorIconAlignment.MiddleLeft);
            m_errorProvider.SetIconPadding(m_hotSwapCheckBox, 3);
            m_errorProvider.SetIconAlignment(m_inputBufferEnabledCheckBox, ErrorIconAlignment.MiddleLeft);
            m_errorProvider.SetIconPadding(m_inputBufferEnabledCheckBox, 3);
            m_errorProvider.SetIconAlignment(m_inputSyncComboBox, ErrorIconAlignment.MiddleRight);
            m_errorProvider.SetIconPadding(m_inputSyncComboBox, 3);
            m_errorProvider.SetIconAlignment(m_interruptComboBox, ErrorIconAlignment.MiddleLeft);
            m_errorProvider.SetIconPadding(m_interruptComboBox, 3);
            m_errorProvider.SetIconAlignment(m_thresholdComboBox, ErrorIconAlignment.MiddleLeft);
            m_errorProvider.SetIconPadding(m_thresholdComboBox, 3);

            errMgr.RegisterSettingOwner(CyPinData.Key.INPUT_HOT_SWAP, m_errorProvider, m_hotSwapCheckBox);
            errMgr.RegisterSettingOwner(CyPinData.Key.INPUT_BUFFER_ENABLED, m_errorProvider, m_inputBufferEnabledCheckBox);
            errMgr.RegisterSettingOwner(CyPinData.Key.INPUT_SYNC_MODE, m_errorProvider, m_inputSyncComboBox);
            errMgr.RegisterSettingOwner(CyPinData.Key.INPUT_INTERRUPT, m_errorProvider, m_interruptComboBox);
            errMgr.RegisterSettingOwner(CyPinData.Key.INPUT_THRESHOLD, m_errorProvider, m_thresholdComboBox);
            errMgr.RegisterSettingOwner(CyPinData.Key.INPUT_HYSTERESIS, m_errorProvider, m_hysteresisCheckBox);
        }

        private bool CanToggleHysteresis(CyInputThreshold threshold)
        {
            if (threshold != CyInputThreshold.CMOS &&
                    threshold != CyInputThreshold.CMOS_LVTTL &&
                    threshold != CyInputThreshold.LVTTL)
            {
                return true; 
            }
            // GPIO modes have hysteresis always enabled - there is no hw toggle
            return false;
        }

        private void EnableEvents()
        {
            m_hotSwapCheckBox.CheckedChanged += m_hotSwapCheckBox_CheckedChanged;
            m_inputBufferEnabledCheckBox.CheckedChanged += m_inputBufferEnabledCheckBox_CheckedChanged;
            m_inputSyncComboBox.SelectedIndexChanged += m_inputSyncComboBox_SelectedIndexChanged;
            m_interruptComboBox.SelectedIndexChanged += m_interruptComboBox_SelectedIndexChanged;
            m_thresholdComboBox.SelectedIndexChanged += m_thresholdComboBox_SelectedIndexChanged;
            m_hysteresisCheckBox.CheckedChanged += m_hysteresisCheckBox_CheckedChanged;
        }
        private void DisableEvents()
        {
            m_hotSwapCheckBox.CheckedChanged -= m_hotSwapCheckBox_CheckedChanged;
            m_inputBufferEnabledCheckBox.CheckedChanged -= m_inputBufferEnabledCheckBox_CheckedChanged;
            m_inputSyncComboBox.SelectedIndexChanged -= m_inputSyncComboBox_SelectedIndexChanged;
            m_interruptComboBox.SelectedIndexChanged -= m_interruptComboBox_SelectedIndexChanged;
            m_thresholdComboBox.SelectedIndexChanged -= m_thresholdComboBox_SelectedIndexChanged;
            m_hysteresisCheckBox.CheckedChanged -= m_hysteresisCheckBox_CheckedChanged;
        }

        internal void UpdateData(IList<CyPinData.PerPin> pins)
        {
            m_pins = pins;

            CheckState hotSwap = pins[0].InputHotSwap ? CheckState.Checked : CheckState.Unchecked;
            CheckState hysteresis;
            hysteresis = pins[0].InputHysteresis ? CheckState.Checked : CheckState.Unchecked;
            CheckState inputBuffer = pins[0].InputBufferEnabled ? CheckState.Checked : CheckState.Unchecked;
            int threshold = Utils.GetIndex<CyInputThreshold>(m_thresholdComboBox, pins[0].InputThreshold);
            int interrupt = Utils.GetIndex<CyInputInterruptTrigger>(m_interruptComboBox, pins[0].InputInterrupt);
            int sync = Utils.GetIndex<CyInputSyncMode>(m_inputSyncComboBox, pins[0].InputSyncMode);

            for (int i = 1; i < pins.Count; i++)
            {
                if (hotSwap != (pins[i].InputHotSwap ? CheckState.Checked : CheckState.Unchecked))
                    hotSwap = CheckState.Indeterminate;
                if (hysteresis != (pins[i].InputHysteresis ? CheckState.Checked : CheckState.Unchecked))
                    hysteresis = CheckState.Indeterminate;
                if (inputBuffer != (pins[i].InputBufferEnabled ? CheckState.Checked : CheckState.Unchecked))
                    inputBuffer = CheckState.Indeterminate;

                if (threshold != (Utils.GetIndex<CyInputThreshold>(m_thresholdComboBox, pins[i].InputThreshold)))
                    threshold = -1;
                if (interrupt != (Utils.GetIndex<CyInputInterruptTrigger>(m_interruptComboBox, pins[i].InputInterrupt)))
                    interrupt = -1;
                if (sync != (Utils.GetIndex<CyInputSyncMode>(m_inputSyncComboBox, pins[i].InputSyncMode)))
                    sync = -1;
            }

            DisableEvents();

            if (CanToggleHysteresis(pins[0].InputThreshold))
            {
                m_hysteresisCheckBox.Enabled = true;
                m_hysteresisCheckBox.CheckState = hysteresis;
            }
            else // Hysteresis is always enabled for GPIOs
            {
                m_hysteresisCheckBox.Enabled = false;
                m_hysteresisCheckBox.CheckState = CheckState.Checked;
            }

            m_hotSwapCheckBox.CheckState = hotSwap;
            m_inputBufferEnabledCheckBox.CheckState = inputBuffer;
            m_thresholdComboBox.SelectedIndex = threshold;
            m_interruptComboBox.SelectedIndex = interrupt;
            m_inputSyncComboBox.SelectedIndex = sync;

            EnableEvents();
        }

        private void m_thresholdComboBox_SelectedIndexChanged(object sender, EventArgs e)
        {
            CyInputThreshold newThreshold = 
                ((CyComboItem<CyInputThreshold>)m_thresholdComboBox.SelectedItem).Item;

            foreach (CyPinData.PerPin pin in m_pins)
                pin.InputThreshold = newThreshold;
             
            if(CanToggleHysteresis(newThreshold))
                m_hysteresisCheckBox.Enabled = true;
            else
            {
                m_hysteresisCheckBox.Enabled = false;
                m_hysteresisCheckBox.Checked = true; // Hysteresis always enabled for GPIO
            }

            // Threshold can impact SIO status - make sure the list is updated to reflect this
            m_onSIOStateChanged();
        }

        private void m_interruptComboBox_SelectedIndexChanged(object sender, EventArgs e)
        {
            foreach (CyPinData.PerPin pin in m_pins)
                pin.InputInterrupt = ((CyComboItem<CyInputInterruptTrigger>)m_interruptComboBox.SelectedItem).Item;
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

        private void m_hotSwapCheckBox_CheckedChanged(object sender, EventArgs e)
        {
            foreach (CyPinData.PerPin pin in m_pins)
                pin.InputHotSwap = m_hotSwapCheckBox.Checked;
            m_onSIOStateChanged(); // Hot-swap can impact "SIO-ness"
        }
    }
}
