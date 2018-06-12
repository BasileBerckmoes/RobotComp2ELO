/*******************************************************************************
* Copyright 2008-2014, Cypress Semiconductor Corporation.  All rights reserved.
* You may use this file only in accordance with the license, terms, conditions, 
* disclaimers, and limitations in the end user license agreement accompanying 
* the software package with which this file was provided.
********************************************************************************/

using System;
using System.Collections.Generic;
using System.Windows.Forms;

namespace Cypress.Comps.PinsAndPorts.cy_pins_v2_20
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
            CyPinData.ErrorMgrKey.INPUT_MULTIPLIER,
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
            bool showVrefInternalThreshold = showSioThreshold && (!deviceSupport.HasData || deviceSupport.IsPSoC4);
            // CMOS 1.8V is available on all devices with GPIOv2 or later. 
            bool showCmosThreshold = !deviceSupport.HasData || deviceSupport.GPIOVersion > 1;
            bool showSingleSync = !deviceSupport.HasData || deviceSupport.HasPortAdapter;
            bool showDblSync = (!deviceSupport.HasData || deviceSupport.IsPSoC3 || deviceSupport.IsPSoC5 || deviceSupport.HasPortAdapter);
            foreach (CyPinData.PerPin pin in pins.Pins)
            {
                showSioThreshold |= CyPinData.PerPin.RequiresSio(pin.InputThreshold);
                showVrefInternalThreshold |= pin.InputThreshold == CyInputThreshold.VREF_INTERNAL;
                showVrefInternalThreshold |= pin.InputThreshold == CyInputThreshold.PT5_VREF_INTERNAL;
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
            m_inputMultiplierComboBox.Visible = showSioThreshold; // Multiplier is always one when there are no SIOs
            if (showSioThreshold)
            {
                m_thresholdComboBox.Items.Add(
                    new CyComboItem<CyInputThreshold>(CyInputThreshold.VDDIO, "Vddio"));
                m_thresholdComboBox.Items.Add(
                    new CyComboItem<CyInputThreshold>(CyInputThreshold.PT5_VREF, "0.5 x Vref"));
                m_thresholdComboBox.Items.Add(
                    new CyComboItem<CyInputThreshold>(CyInputThreshold.VREF, "Vref"));
                if (showVrefInternalThreshold)
                {
                    m_thresholdComboBox.Items.Add(
                        new CyComboItem<CyInputThreshold>(CyInputThreshold.PT5_VREF_INTERNAL, "0.5 x Vref (internal)"));
                    m_thresholdComboBox.Items.Add(
                        new CyComboItem<CyInputThreshold>(CyInputThreshold.VREF_INTERNAL, "Vref (internal)"));
                }
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
            errMgr.RegisterSettingOwner(CyPinData.ErrorMgrKey.INPUT_MULTIPLIER, m_errorProvider, m_inputMultiplierComboBox);
        }

        private void UpdateHysteresisDisplay(IEnumerable<CyPinData.PerPin> pins)
        {
            // SIO Hysteresis off option is only enabled if all selected pins use an SIO-specific threshold
            bool hysteresisConfigurable;
            if (!m_deviceSupport.IsPSoC4 || m_deviceSupport.IsTSG4) // This is configurable on TSG4; not on other PSoC4 devices
            {
                hysteresisConfigurable = true;
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
            }
            else
                hysteresisConfigurable = false; // Never configurable on PSoC 4 SIOs

            // When the hysteresis checkbox first becomes available, we want it to default to false - but we 
            // don't want to force it back to false every time they change between SIO settings
            if (!m_hysteresisCheckBox.Enabled && hysteresisConfigurable)
                m_hysteresisCheckBox.Checked = false;
            else if (!hysteresisConfigurable)
                m_hysteresisCheckBox.Checked = true; // Hysteresis is always on for standard GPIOs

            m_hysteresisCheckBox.Enabled = hysteresisConfigurable;
        }

        internal void PopulateMultiplierDropdown(int prevIdx)
        {
            m_inputMultiplierComboBox.Items.Clear();
            List<double> multipliers = new List<double>();
            CyInputThreshold level;
            if (m_thresholdComboBox.SelectedItem != null)
                level = ((CyComboItem<CyInputThreshold>)m_thresholdComboBox.SelectedItem).Item;
            else
                level = CyInputThreshold.CMOS_LVTTL; // Unknown level => multiplier is disabled, so just show 1x
            switch (level)
            {
               // Only 1x allowed for non 0.5x vref variants; see CDT 220839
               case CyInputThreshold.PT5_VREF:
               case CyInputThreshold.PT5_VREF_INTERNAL:
                    if (!m_deviceSupport.IsPSoC4 && prevIdx < 1) // Show the full list if switching devices
                    {
                        multipliers.Add(CyPinData.VrefMultiplierValues[CyPinData.DefaultMultiplierIdx]); // x1
                        m_inputMultiplierComboBox.Enabled = false;
                    }
                    else
                    {
                        multipliers.AddRange(CyPinData.VrefMultiplierValues);
                        m_inputMultiplierComboBox.Enabled = true;
                    }
                    break;
                case CyInputThreshold.VDDIO:
                    multipliers.AddRange(CyPinData.VddioMultiplierValues);
                    m_inputMultiplierComboBox.Enabled = true;
                    break;
                default: // Only 1x permitted in all other cases, including unknown
                    multipliers.Add(CyPinData.VrefMultiplierValues[CyPinData.DefaultMultiplierIdx]); // x1
                    m_inputMultiplierComboBox.Enabled = false;
                    break;
            }
            foreach(double val in multipliers)
                m_inputMultiplierComboBox.Items.Add("x" + val);

            // Preserve the previous index if possible; otherwise default to 1
            if (prevIdx < m_inputMultiplierComboBox.Items.Count)
                m_inputMultiplierComboBox.SelectedIndex = prevIdx;
            else
                m_inputMultiplierComboBox.SelectedIndex = CyPinData.DefaultMultiplierIdx;
        }

        private void UpdateDedicatedIsrCheckbox(bool isrEnabled)
        {
            // Enable only if a.)the device has an all-ports interrupt, and b.)the isr is enabled
            m_dedicatedInterruptCheckBox.Enabled = isrEnabled && m_deviceSupport.HasAllPortsInterrupt;
        }

        private void EnableEvents()
        {
            m_inputBufferEnabledCheckBox.CheckedChanged += m_inputBufferEnabledCheckBox_CheckedChanged;
            m_inputSyncComboBox.SelectedIndexChanged += m_inputSyncComboBox_SelectedIndexChanged;
            m_interruptComboBox.SelectedIndexChanged += m_interruptComboBox_SelectedIndexChanged;
            m_thresholdComboBox.SelectedIndexChanged += m_thresholdComboBox_SelectedIndexChanged;
            m_hysteresisCheckBox.CheckedChanged += m_hysteresisCheckBox_CheckedChanged;
            m_dedicatedInterruptCheckBox.CheckedChanged += m_dedicatedInterruptCheckBox_CheckChanged;
            m_inputMultiplierComboBox.SelectedIndexChanged += m_inputMultiplierComboBox_SelectedIndexChanged;
        }
        private void DisableEvents()
        {
            m_inputBufferEnabledCheckBox.CheckedChanged -= m_inputBufferEnabledCheckBox_CheckedChanged;
            m_inputSyncComboBox.SelectedIndexChanged -= m_inputSyncComboBox_SelectedIndexChanged;
            m_interruptComboBox.SelectedIndexChanged -= m_interruptComboBox_SelectedIndexChanged;
            m_thresholdComboBox.SelectedIndexChanged -= m_thresholdComboBox_SelectedIndexChanged;
            m_hysteresisCheckBox.CheckedChanged -= m_hysteresisCheckBox_CheckedChanged;
            m_dedicatedInterruptCheckBox.CheckedChanged -= m_dedicatedInterruptCheckBox_CheckChanged;
            m_inputMultiplierComboBox.SelectedIndexChanged -= m_inputMultiplierComboBox_SelectedIndexChanged;
        }

        internal void UpdateData()
        {
            DisableEvents();

            UpdateHysteresisDisplay(m_pins);

            CheckState inputBuffer = m_pins[0].InputBufferEnabled ? CheckState.Checked : CheckState.Unchecked;
            CheckState hysteresis = m_pins[0].InputHysteresis ? CheckState.Checked :  CheckState.Unchecked;
            CheckState dedicatedIsr = m_pins[0].DedicatedInterrupt ? CheckState.Checked : CheckState.Unchecked;
            int threshold = Utils.GetIndex(m_thresholdComboBox, m_pins[0].InputThreshold);
            int interrupt = Utils.GetIndex(m_interruptComboBox, m_pins[0].InputInterrupt);
            int sync = Utils.GetIndex(m_inputSyncComboBox, m_pins[0].InputSyncMode);
            for (int i = 1; i < m_pins.Count; i++)
            {
                if (inputBuffer != (m_pins[i].InputBufferEnabled ? CheckState.Checked : CheckState.Unchecked))
                    inputBuffer = CheckState.Indeterminate;
                if (hysteresis != (m_pins[i].InputHysteresis ? CheckState.Checked : CheckState.Unchecked))
                    hysteresis = CheckState.Indeterminate;
                if (dedicatedIsr != (m_pins[i].DedicatedInterrupt ? CheckState.Checked : CheckState.Unchecked))
                    dedicatedIsr = CheckState.Indeterminate;
                if (threshold != (Utils.GetIndex<CyInputThreshold>(m_thresholdComboBox, m_pins[i].InputThreshold)))
                    threshold = -1;
                if (interrupt != (Utils.GetIndex<CyInputInterruptTrigger>(m_interruptComboBox, m_pins[i].InputInterrupt)))
                    interrupt = -1;
                if (sync != (Utils.GetIndex<CyInputSyncMode>(m_inputSyncComboBox, m_pins[i].InputSyncMode)))
                    sync = -1;
            }

            // Have to look this up separately because we need to know our threshold in order to know where to look up
            int multiplier;
            if (threshold < 0) // Thresholds mismatch, so multipliers can't match
                multiplier = -1;
            else
            {
                double[] arr;
                switch(m_pins[0].InputThreshold)
                {
                    case CyInputThreshold.VDDIO:
                        arr = CyPinData.VddioMultiplierValues;
                        break;
                    case CyInputThreshold.VREF:
                    case CyInputThreshold.VREF_INTERNAL:
                    case CyInputThreshold.PT5_VREF:
                    case CyInputThreshold.PT5_VREF_INTERNAL:
                        arr = CyPinData.VrefMultiplierValues;
                        break;
                    default:
                        arr = null;
                        break;
                }
                if (arr == null) // Configuration not supported; must be 1x
                    multiplier = CyPinData.DefaultMultiplierIdx;
                else
                {
                    multiplier = Array.IndexOf(arr, m_pins[0].InputMultiplier);
                    for (int i = 1; i < m_pins.Count; ++i)
                    {
                        if (Array.IndexOf(arr, m_pins[i].InputMultiplier) != multiplier)
                        {
                            multiplier = -1;
                            break;
                        }
                    }
                }
            }
            m_hysteresisCheckBox.CheckState = hysteresis;
            m_dedicatedInterruptCheckBox.CheckState = dedicatedIsr;
            m_inputBufferEnabledCheckBox.CheckState = inputBuffer;
            m_thresholdComboBox.SelectedIndex = threshold;
            m_interruptComboBox.SelectedIndex = interrupt;
            m_inputSyncComboBox.SelectedIndex = sync;
            PopulateMultiplierDropdown(multiplier); // Needs to happen after we set the threshold
            if(multiplier >= m_inputMultiplierComboBox.Items.Count) // Can happen switching devices
                multiplier = 0;
            m_inputMultiplierComboBox.SelectedIndex = multiplier;
            UpdateDedicatedIsrCheckbox(interrupt > 0);

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
            UpdateDedicatedIsrCheckbox(trigger != CyInputInterruptTrigger.NONE);
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

        private void m_dedicatedInterruptCheckBox_CheckChanged(object sender, EventArgs e)
        {
            foreach (CyPinData.PerPin pin in m_pins)
                pin.DedicatedInterrupt = m_dedicatedInterruptCheckBox.Checked;
        }

        void m_inputMultiplierComboBox_SelectedIndexChanged(object sender, EventArgs e)
        {
            double multiplier;
            switch(((CyComboItem<CyInputThreshold>)m_thresholdComboBox.SelectedItem).Item)
            {
                case CyInputThreshold.VREF:
                case CyInputThreshold.PT5_VREF:
                case CyInputThreshold.VREF_INTERNAL:
                case CyInputThreshold.PT5_VREF_INTERNAL:
                    multiplier = CyPinData.VrefMultiplierValues[m_inputMultiplierComboBox.SelectedIndex];
                    break;
                case CyInputThreshold.VDDIO:
                    multiplier = CyPinData.VddioMultiplierValues[m_inputMultiplierComboBox.SelectedIndex];
                    break;
                default:
                    multiplier = 1;
                    break;
            }
            foreach (CyPinData.PerPin pin in m_pins)
                pin.InputMultiplier = multiplier;
        }
    }
}
