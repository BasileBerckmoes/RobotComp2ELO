/*******************************************************************************
* Copyright 2008-2016, Cypress Semiconductor Corporation.  All rights reserved.
* You may use this file only in accordance with the license, terms, conditions, 
* disclaimers, and limitations in the end user license agreement accompanying 
* the software package with which this file was provided.
********************************************************************************/

using System;
using System.Collections.Generic;
using System.Diagnostics;
using System.Diagnostics.CodeAnalysis;
using System.Linq;
using System.Windows.Forms;

namespace Cypress.Comps.PinsAndPorts.GPIO_PDL_v1_0
{
    [ExcludeFromCodeCoverage]
    public partial class CyOutputControl : UserControl
    {
        internal static readonly Formal.ErrorKey[] OwnedSettings = new Formal.ErrorKey[]
        {
            Formal.ErrorKey.OUTPUT_ENABLE_SYNCHRONIZED,
            Formal.ErrorKey.OUTPUT_DRIVE_LEVEL,
            Formal.ErrorKey.OUTPUT_CURR_CAP,
            Formal.ErrorKey.OUTPUT_SYNC_MODE,
            Formal.ErrorKey.OUTPUT_MULTIPLIER,
        };

        private IList<CyPinData.PerPin> m_pins;
        private Action m_onSIOStateChanged;

        public CyOutputControl(CyDeviceSupport deviceSupport, CyErrorManager errMgr, CyPinData pins,
                                Action sioStateChanged)
        {
            InitializeComponent();

            m_onSIOStateChanged = sioStateChanged;

            // Some selections should only be shown if they are available or already in use
            IEnumerable<CyOutputCurrentCap> currCaps = deviceSupport.AvailableCurrentCaps;
            bool showCap5 = currCaps.Contains(CyOutputCurrentCap.Source_5ma_Sink_5ma);
            bool showCap8 = currCaps.Contains(CyOutputCurrentCap.Source_8ma_Sink_8ma);
            bool showCap16 = currCaps.Contains(CyOutputCurrentCap.Source_16ma_Sink_16ma);
            bool showCap40 = currCaps.Contains(CyOutputCurrentCap.Source_40ma_Sink_40ma);
            bool showOutModeSync = deviceSupport.HasSyncModes;
            bool showOeSync = deviceSupport.HasSyncModes;
            bool showOutLevelVref = deviceSupport.HasOutLevelVref;
            bool showInternalVref = deviceSupport.HasInternalVref;
            bool showVrefMultipliers = showOutLevelVref;
            foreach (CyPinData.PerPin pin in pins.Pins)
            {
                showCap5 |= pin.OutputCurrentCap == CyOutputCurrentCap.Source_5ma_Sink_5ma;
                showCap8 |= pin.OutputCurrentCap == CyOutputCurrentCap.Source_8ma_Sink_8ma;
                showCap16 |= pin.OutputCurrentCap == CyOutputCurrentCap.Source_16ma_Sink_16ma;
                showCap40 |= pin.OutputCurrentCap == CyOutputCurrentCap.Source_40ma_Sink_40ma;
                showOutModeSync |= pin.OutputSyncMode == CySyncMode.Single;
                showOeSync |= pin.OutputEnableSynchronized;
                showOutLevelVref |= pin.OutputDriveLevel != CyOutputDriveLevel.Vddio;
                showInternalVref |= pin.OutputDriveLevel == CyOutputDriveLevel.Vref_Internal;
                showVrefMultipliers |= pin.OutputMultiplier != 1.0;
            }

            m_slewRateComboBox.AddItem(CyOutputSlewRate.Slow, Resource1.Slow);
            m_slewRateComboBox.AddItem(CyOutputSlewRate.Fast, Resource1.Fast);

            m_driveLevelComboBox.AddItem(CyOutputDriveLevel.Vddio, Resource1.Vddio);
            if (showOutLevelVref)
                m_driveLevelComboBox.AddItem(CyOutputDriveLevel.Vref, Resource1.Vref);
            if (showInternalVref)
                m_driveLevelComboBox.AddItem(CyOutputDriveLevel.Vref_Internal, Resource1.VrefInternal);

            Action<CyOutputCurrentCap> AddCurrentCap = current =>
                {
                    string display = string.Format(Resource1.Prompt_SourceSink, Formal.AsString(current));
                    m_currCapComboBox.AddItem(current, display);
                };
            if (showCap5)
                AddCurrentCap(CyOutputCurrentCap.Source_5ma_Sink_5ma);
            if (showCap8)
                AddCurrentCap(CyOutputCurrentCap.Source_8ma_Sink_8ma);
            if (showCap16)
                AddCurrentCap(CyOutputCurrentCap.Source_16ma_Sink_16ma);
            if (showCap40)
                AddCurrentCap(CyOutputCurrentCap.Source_40ma_Sink_40ma);

            m_driveStrengthComboBox.AddItem(CyDriveStrength.Full, Resource1.Full);
            m_driveStrengthComboBox.AddItem(CyDriveStrength.Half, Resource1.Half);
            m_driveStrengthComboBox.AddItem(CyDriveStrength.Quarter, Resource1.Quarter);
            m_driveStrengthComboBox.AddItem(CyDriveStrength.Eighth, Resource1.Eighth);

            m_outputModeComboBox.AddItem(CySyncMode.Transparent, Resource1.SyncMode_Transparent);
            if (showOutModeSync)
                m_outputModeComboBox.AddItem(CySyncMode.Single, Resource1.SyncMode_SingleSync);

            m_oeSyncCheckBox.Visible = showOeSync;

            if (!showVrefMultipliers)
            {
                m_driveMultiplierComboBox.Visible = false;
                // Expand the drive level combo box width to fill the space that was taken by the multiplier
                m_driveLevelComboBox.Width = m_currCapComboBox.Width;
            }

            EnableEvents();

            m_errorProvider.SetIconAlignment(m_slewRateComboBox, ErrorIconAlignment.MiddleLeft);
            m_errorProvider.SetIconPadding(m_slewRateComboBox, 3);
            m_errorProvider.SetIconAlignment(m_driveLevelComboBox, ErrorIconAlignment.MiddleLeft);
            m_errorProvider.SetIconPadding(m_driveLevelComboBox, 3);
            m_errorProvider.SetIconAlignment(m_currCapComboBox, ErrorIconAlignment.MiddleLeft);
            m_errorProvider.SetIconPadding(m_currCapComboBox, 3);
            m_errorProvider.SetIconAlignment(m_oeSyncCheckBox, ErrorIconAlignment.MiddleLeft);
            m_errorProvider.SetIconPadding(m_oeSyncCheckBox, 3);

            errMgr.RegisterKeyOwner(Formal.ErrorKey.OUTPUT_ENABLE_SYNCHRONIZED, m_errorProvider, m_oeSyncCheckBox);
            errMgr.RegisterKeyOwner(Formal.ErrorKey.OUTPUT_DRIVE_LEVEL, m_errorProvider, m_driveLevelComboBox);
            errMgr.RegisterKeyOwner(Formal.ErrorKey.OUTPUT_CURR_CAP, m_errorProvider, m_currCapComboBox);
            errMgr.RegisterKeyOwner(Formal.ErrorKey.OUTPUT_SYNC_MODE, m_errorProvider, m_outputModeComboBox);
            errMgr.RegisterKeyOwner(Formal.ErrorKey.OUTPUT_MULTIPLIER, m_errorProvider, m_driveMultiplierComboBox);
        }

        private void EnableEvents()
        {
            m_oeSyncCheckBox.CheckedChanged += m_oeSyncCheckBox_CheckedChanged;
            m_slewRateComboBox.SelectedIndexChanged += m_slewRateComboBox_SelectedIndexChanged;
            m_driveLevelComboBox.SelectedIndexChanged += m_driveLevelComboBox_SelectedIndexChanged;
            m_driveMultiplierComboBox.SelectedIndexChanged += m_driveMultiplierComboBox_SelectedIndexChanged;
            m_currCapComboBox.SelectedIndexChanged += m_currCapComboBox_SelectedIndexChanged;
            m_outputModeComboBox.SelectedIndexChanged += m_outputModeComboBox_SelectedIndexChanged;
            m_driveStrengthComboBox.SelectedIndexChanged += m_driveStrengthComboBox_SelectedIndexChanged;
        }

        private void DisableEvents()
        {
            m_oeSyncCheckBox.CheckedChanged -= m_oeSyncCheckBox_CheckedChanged;
            m_slewRateComboBox.SelectedIndexChanged -= m_slewRateComboBox_SelectedIndexChanged;
            m_driveLevelComboBox.SelectedIndexChanged -= m_driveLevelComboBox_SelectedIndexChanged;
            m_driveMultiplierComboBox.SelectedIndexChanged -= m_driveMultiplierComboBox_SelectedIndexChanged;
            m_currCapComboBox.SelectedIndexChanged -= m_currCapComboBox_SelectedIndexChanged;
            m_outputModeComboBox.SelectedIndexChanged -= m_outputModeComboBox_SelectedIndexChanged;
            m_driveStrengthComboBox.SelectedIndexChanged -= m_driveStrengthComboBox_SelectedIndexChanged;
        }

        internal void UpdateData()
        {
            CheckState oeSync = m_pins[0].OutputEnableSynchronized ? CheckState.Checked : CheckState.Unchecked;
            int slew = m_slewRateComboBox.GetIndex(m_pins[0].OutputSlewRate);
            int level = m_driveLevelComboBox.GetIndex(m_pins[0].OutputDriveLevel);
            int cap = m_currCapComboBox.GetIndex(m_pins[0].OutputCurrentCap);
            int mode = m_outputModeComboBox.GetIndex(m_pins[0].OutputSyncMode);
            int strength = m_driveStrengthComboBox.GetIndex(m_pins[0].DriveStrength);

            // Look up the multiplier in the array; our combo indexes are constructed to always match it, and this 
            // lets us look up the index in our main loop, which happens before we've populated the combo box
            int multiplier = Formal.VrefMultipliers.IndexOf(m_pins[0].OutputMultiplier);

            foreach (CyPinData.PerPin pin in m_pins.Skip(1))
            {
                if (oeSync != (pin.OutputEnableSynchronized ? CheckState.Checked : CheckState.Unchecked))
                    oeSync = CheckState.Indeterminate;

                if (slew != m_slewRateComboBox.GetIndex(pin.OutputSlewRate))
                    slew = -1;
                if (level != m_driveLevelComboBox.GetIndex(pin.OutputDriveLevel))
                    level = -1;
                if (cap != m_currCapComboBox.GetIndex(pin.OutputCurrentCap))
                    cap = -1;
                if (mode != m_outputModeComboBox.GetIndex(pin.OutputSyncMode))
                    mode = -1;
                if (multiplier != Formal.VrefMultipliers.IndexOf(pin.OutputMultiplier))
                    multiplier = -1;
                if (strength != m_driveStrengthComboBox.GetIndex(pin.DriveStrength))
                    strength = -1;
            }

            DisableEvents();

            bool anyI2C = m_pins.Any(pin => CyMaxFrequency.MHz_NA == pin.MaxFrequency);
            m_slewRateComboBox.Enabled = !anyI2C;
 
            m_oeSyncCheckBox.CheckState = oeSync;
            m_slewRateComboBox.SelectedIndex = slew;
            m_driveLevelComboBox.SelectedIndex = level;
            PopulateMultiplierDropdown(multiplier); // Needs to happen after we set the drive level
            if (multiplier >= m_driveMultiplierComboBox.Items.Count) // Can happen switching devices
                multiplier = 0;
            m_driveMultiplierComboBox.SelectedIndex = multiplier;
            m_currCapComboBox.SelectedIndex = cap;
            m_outputModeComboBox.SelectedIndex = mode;
            m_driveStrengthComboBox.SelectedIndex = strength;

            EnableEvents();
        }

        internal void UpdateData(IList<CyPinData.PerPin> pins)
        {
            m_pins = pins;
            UpdateData();
        }

        internal void PopulateMultiplierDropdown(int prevIdx)
        { 
            m_driveMultiplierComboBox.Items.Clear();
            List<double> multipliers = new List<double>();
            CyOutputDriveLevel level = (m_driveLevelComboBox.SelectedItem != null)
                ? ((CyComboItem<CyOutputDriveLevel>)m_driveLevelComboBox.SelectedItem).Item
                : CyOutputDriveLevel.Vddio; // Unknown level => multiplier is disabled, so just show 1x
            switch (level)
            {
                case CyOutputDriveLevel.Vref:
                case CyOutputDriveLevel.Vref_Internal:
                    multipliers.AddRange(Formal.VrefMultipliers.Values);
                    m_driveMultiplierComboBox.Enabled = true;
                    break;
                default: // Only 1x permitted in all other cases, including unknown
                    multipliers.Add(Formal.VrefMultipliers.Default); // x1
                    m_driveMultiplierComboBox.Enabled = false;
                    break;
            }
            foreach (double val in multipliers)
                m_driveMultiplierComboBox.Items.Add("x" + val);

            // Preserve the previous index if possible; otherwise default to 1
            if (prevIdx >= m_driveMultiplierComboBox.Items.Count) prevIdx = Formal.VrefMultipliers.Index_Default;
            m_driveMultiplierComboBox.SelectedIndex = prevIdx;
        }

        void m_currCapComboBox_SelectedIndexChanged(object sender, EventArgs e)
        {
            foreach (CyPinData.PerPin pin in m_pins)
                pin.OutputCurrentCap = ((CyComboItem<CyOutputCurrentCap>)m_currCapComboBox.SelectedItem).Item;
            m_onSIOStateChanged(); // Output current can impact "SIO-ness"
        }

        void m_driveStrengthComboBox_SelectedIndexChanged(object sender, EventArgs e)
        {
            foreach (CyPinData.PerPin pin in m_pins)
                pin.DriveStrength = ((CyComboItem<CyDriveStrength>)m_driveStrengthComboBox.SelectedItem).Item;
        }

        void m_driveLevelComboBox_SelectedIndexChanged(object sender, EventArgs e)
        {
            foreach (CyPinData.PerPin pin in m_pins)
                pin.OutputDriveLevel = ((CyComboItem<CyOutputDriveLevel>)m_driveLevelComboBox.SelectedItem).Item;
            m_onSIOStateChanged(); // Drive level can impact "SIO-ness"

            DisableEvents();
            PopulateMultiplierDropdown(m_driveMultiplierComboBox.SelectedIndex); // Valid multiplier values can change based on the drive level
            EnableEvents();
        }

        void m_driveMultiplierComboBox_SelectedIndexChanged(object sender, EventArgs e)
        {
            double multiplier = Formal.VrefMultipliers.At(m_driveMultiplierComboBox.SelectedIndex);
            foreach (CyPinData.PerPin pin in m_pins)
                pin.OutputMultiplier = multiplier;
        }

        void m_outputModeComboBox_SelectedIndexChanged(object sender, EventArgs e)
        {
            foreach (CyPinData.PerPin pin in m_pins)
                pin.OutputSyncMode = ((CyComboItem<CySyncMode>)m_outputModeComboBox.SelectedItem).Item;
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
