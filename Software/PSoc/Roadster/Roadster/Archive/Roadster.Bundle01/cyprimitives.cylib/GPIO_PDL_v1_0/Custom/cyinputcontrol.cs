/*******************************************************************************
* Copyright 2008-2016, Cypress Semiconductor Corporation.  All rights reserved.
* You may use this file only in accordance with the license, terms, conditions, 
* disclaimers, and limitations in the end user license agreement accompanying 
* the software package with which this file was provided.
********************************************************************************/

using System;
using System.Collections.Generic;
using System.Diagnostics.CodeAnalysis;
using System.Linq;
using System.Windows.Forms;

namespace Cypress.Comps.PinsAndPorts.GPIO_PDL_v1_0
{
    [ExcludeFromCodeCoverage]
    public partial class CyInputControl : UserControl
    {
        internal static readonly Formal.ErrorKey[] OwnedSettings = new Formal.ErrorKey[]
        {
            Formal.ErrorKey.INPUT_HOT_SWAP,
            Formal.ErrorKey.INPUT_SYNC_MODE,
            Formal.ErrorKey.INPUT_INTERRUPT,
            Formal.ErrorKey.INPUT_THRESHOLD,
            Formal.ErrorKey.INPUT_MULTIPLIER,
        };

        private IList<CyPinData.PerPin> m_pins;
        private Action m_onSIOStateChanged;
        
        public CyInputControl(CyDeviceSupport deviceSupport, CyErrorManager errMgr, CyPinData pins, 
                                Action onSioStateChanged)
        {
            InitializeComponent();
            m_onSIOStateChanged = onSioStateChanged;
            bool showSioThreshold = deviceSupport.HasSIO;
            bool showVrefInternalThreshold = showSioThreshold;
            bool showSingleSync = deviceSupport.HasSyncModes;
            bool showDblSync = deviceSupport.HasSyncModes;
            foreach (CyPinData.PerPin pin in pins.Pins)
            {
                showSioThreshold |= CyPinData.PerPin.RequiresSio(pin.InputThreshold);
                showVrefInternalThreshold |= pin.InputThreshold == CyInputThreshold.Vref_internal;
                showVrefInternalThreshold |= pin.InputThreshold == CyInputThreshold.Pt5_Vref_internal;
                showSingleSync |= (pin.InputSyncMode == CySyncMode.Single);
                showDblSync |= (pin.InputSyncMode == CySyncMode.Double);
            }

            m_thresholdComboBox.AddItem(CyInputThreshold.CMOS, Resource1.CMOS);
            m_thresholdComboBox.AddItem(CyInputThreshold.CMOS_LVTTL, Resource1.CMOS_LVTTL);
            m_thresholdComboBox.AddItem(CyInputThreshold.LVTTL, Resource1.LVTTL);
            m_inputMultiplierComboBox.Visible = showSioThreshold; // Multiplier is always one when there are no SIOs
            if (showSioThreshold)
            {
                m_thresholdComboBox.AddItem(CyInputThreshold.Vddio, Resource1.Vddio);
                m_thresholdComboBox.AddItem(CyInputThreshold.Pt5_Vref, Resource1.HalfVref);
                m_thresholdComboBox.AddItem(CyInputThreshold.Vref, Resource1.Vref);
                if (showVrefInternalThreshold)
                {
                    m_thresholdComboBox.AddItem(CyInputThreshold.Pt5_Vref_internal, Resource1.HalfVrefInternal);
                    m_thresholdComboBox.AddItem(CyInputThreshold.Vref_internal, Resource1.VrefInternal);
                }
            }

            m_interruptComboBox.AddItem(CyInputInterruptTrigger.None, Resource1.None);
            m_interruptComboBox.AddItem(CyInputInterruptTrigger.Rising_edge, Resource1.RisingEdge);
            m_interruptComboBox.AddItem(CyInputInterruptTrigger.Falling_edge, Resource1.FallingEdge);
            m_interruptComboBox.AddItem(CyInputInterruptTrigger.Both_edges, Resource1.BothEdges);

            if (showDblSync)
                m_inputSyncComboBox.AddItem(CySyncMode.Double, Resource1.SyncMode_DoubleSync);
            if (showSingleSync)
                m_inputSyncComboBox.AddItem(CySyncMode.Single, Resource1.SyncMode_SingleSync);
            m_inputSyncComboBox.AddItem(CySyncMode.Transparent, Resource1.SyncMode_Transparent);

            EnableEvents();

            m_errorProvider.SetIconAlignment(m_inputSyncComboBox, ErrorIconAlignment.MiddleRight);
            m_errorProvider.SetIconPadding(m_inputSyncComboBox, 3);
            m_errorProvider.SetIconAlignment(m_interruptComboBox, ErrorIconAlignment.MiddleLeft);
            m_errorProvider.SetIconPadding(m_interruptComboBox, 3);
            m_errorProvider.SetIconAlignment(m_thresholdComboBox, ErrorIconAlignment.MiddleLeft);
            m_errorProvider.SetIconPadding(m_thresholdComboBox, 3);

            errMgr.RegisterKeyOwner(Formal.ErrorKey.INPUT_SYNC_MODE, m_errorProvider, m_inputSyncComboBox);
            errMgr.RegisterKeyOwner(Formal.ErrorKey.INPUT_INTERRUPT, m_errorProvider, m_interruptComboBox);
            errMgr.RegisterKeyOwner(Formal.ErrorKey.INPUT_THRESHOLD, m_errorProvider, m_thresholdComboBox);
            errMgr.RegisterKeyOwner(Formal.ErrorKey.INPUT_MULTIPLIER, m_errorProvider, m_inputMultiplierComboBox);
        }

        internal void PopulateMultiplierDropdown(int prevIdx)
        {
            List<double> multipliers = new List<double>();
            CyInputThreshold level;
            if (m_thresholdComboBox.SelectedItem != null)
                level = ((CyComboItem<CyInputThreshold>)m_thresholdComboBox.SelectedItem).Item;
            else
                level = CyInputThreshold.Default; // Unknown level => multiplier is disabled, so just show 1x
            switch (level)
            {
               // Only 1x allowed for non 0.5x vref variants; see CDT 220839
               case CyInputThreshold.Pt5_Vref:
               case CyInputThreshold.Pt5_Vref_internal:
                    multipliers.AddRange(Formal.VrefMultipliers.Values);
                    m_inputMultiplierComboBox.Enabled = true;
                    break;
                case CyInputThreshold.Vddio:
                    multipliers.AddRange(Formal.VddioMultipliers.Values);
                    m_inputMultiplierComboBox.Enabled = true;
                    break;
                default: // Only 1x permitted in all other cases, including unknown
                    multipliers.Add(Formal.VrefMultipliers.Default); // x1
                    m_inputMultiplierComboBox.Enabled = false;
                    break;
            }

            int oldCount = m_inputMultiplierComboBox.Items.Count;
            m_inputMultiplierComboBox.Items.Clear();
            foreach (double val in multipliers)
                m_inputMultiplierComboBox.Items.Add("x" + val);
            int newCount = m_inputMultiplierComboBox.Items.Count;

            // Preserve the previous index if possible; otherwise default to a multiplier of 1
            if (prevIdx >= newCount || oldCount != newCount)
                prevIdx = Formal.VrefMultipliers.Index_Default;
            m_inputMultiplierComboBox.SelectedIndex = prevIdx;
        }

        private void EnableEvents()
        {
            m_inputSyncComboBox.SelectedIndexChanged += m_inputSyncComboBox_SelectedIndexChanged;
            m_interruptComboBox.SelectedIndexChanged += m_interruptComboBox_SelectedIndexChanged;
            m_thresholdComboBox.SelectedIndexChanged += m_thresholdComboBox_SelectedIndexChanged;
            m_inputMultiplierComboBox.SelectedIndexChanged += m_inputMultiplierComboBox_SelectedIndexChanged;
        }
        private void DisableEvents()
        {
            m_inputSyncComboBox.SelectedIndexChanged -= m_inputSyncComboBox_SelectedIndexChanged;
            m_interruptComboBox.SelectedIndexChanged -= m_interruptComboBox_SelectedIndexChanged;
            m_thresholdComboBox.SelectedIndexChanged -= m_thresholdComboBox_SelectedIndexChanged;
            m_inputMultiplierComboBox.SelectedIndexChanged -= m_inputMultiplierComboBox_SelectedIndexChanged;
        }

        internal void UpdateData()
        {
            DisableEvents();

            int threshold = m_thresholdComboBox.GetIndex(m_pins[0].InputThreshold);
            int interrupt = m_interruptComboBox.GetIndex(m_pins[0].InputInterrupt);
            int sync = m_inputSyncComboBox.GetIndex(m_pins[0].InputSyncMode);
            foreach (CyPinData.PerPin pin in m_pins.Skip(1))
            {
                if (threshold != m_thresholdComboBox.GetIndex(pin.InputThreshold))
                    threshold = -1;
                if (interrupt != m_interruptComboBox.GetIndex(pin.InputInterrupt))
                    interrupt = -1;
                if (sync != m_inputSyncComboBox.GetIndex(pin.InputSyncMode))
                    sync = -1;
            }

            // Have to look this up separately because we need to know our threshold in order to know where to look up
            int multiplier;
            if (threshold < 0) // Thresholds mismatch, so multipliers can't match
                multiplier = -1;
            else
            {
                switch (m_pins[0].InputThreshold)
                {
                    case CyInputThreshold.Vddio:
                        multiplier = m_pins.All(pin => pin.InputMultiplier == m_pins[0].InputMultiplier)
                            ? Formal.VddioMultipliers.IndexOf(m_pins[0].InputMultiplier)
                            : -1;
                        break;
                    case CyInputThreshold.Vref:
                    case CyInputThreshold.Vref_internal:
                    case CyInputThreshold.Pt5_Vref:
                    case CyInputThreshold.Pt5_Vref_internal:
                        multiplier = m_pins.All(pin => pin.InputMultiplier == m_pins[0].InputMultiplier)
                            ? Formal.VrefMultipliers.IndexOf(m_pins[0].InputMultiplier)
                            : -1;
                        break;
                    default:
                        multiplier = Formal.VrefMultipliers.Index_Default;
                        break;
                }
            }

            // If an I2C mode selected for any pin, disable dropdowns whose values are forced.
            bool anyI2C = m_pins.Any(pin => CyMaxFrequency.MHz_NA == pin.MaxFrequency);
            m_thresholdComboBox.Enabled = !anyI2C;
            m_inputMultiplierComboBox.Enabled = !anyI2C;

            m_inputSyncComboBox.Enabled = m_pins.Any(pin => pin.TypeIsDigitalInputHw);

            m_thresholdComboBox.SelectedIndex = threshold;
            m_interruptComboBox.SelectedIndex = interrupt;
            m_inputSyncComboBox.SelectedIndex = sync;
            PopulateMultiplierDropdown(multiplier); // Needs to happen after we set the threshold
            if (multiplier >= m_inputMultiplierComboBox.Items.Count) // Can happen switching devices
                multiplier = 0;
            m_inputMultiplierComboBox.SelectedIndex = multiplier;

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
                pin.InputSyncMode = ((CyComboItem<CySyncMode>)m_inputSyncComboBox.SelectedItem).Item;
        }

        void m_inputMultiplierComboBox_SelectedIndexChanged(object sender, EventArgs e)
        {
            double multiplier;
            switch (((CyComboItem<CyInputThreshold>)m_thresholdComboBox.SelectedItem).Item)
            {
                case CyInputThreshold.Vref:
                case CyInputThreshold.Pt5_Vref:
                case CyInputThreshold.Vref_internal:
                case CyInputThreshold.Pt5_Vref_internal:
                    multiplier = Formal.VrefMultipliers.At(m_inputMultiplierComboBox.SelectedIndex);
                    break;
                case CyInputThreshold.Vddio:
                    multiplier = Formal.VddioMultipliers.At(m_inputMultiplierComboBox.SelectedIndex);
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
