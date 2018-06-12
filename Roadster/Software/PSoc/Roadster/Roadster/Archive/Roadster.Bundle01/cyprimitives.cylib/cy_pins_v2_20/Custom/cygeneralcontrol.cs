/*******************************************************************************
* Copyright 2008-2014, Cypress Semiconductor Corporation.  All rights reserved.
* You may use this file only in accordance with the license, terms, conditions, 
* disclaimers, and limitations in the end user license agreement accompanying 
* the software package with which this file was provided.
********************************************************************************/

using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Drawing.Imaging;
using System.Windows.Forms;
using System.Diagnostics;
using System.IO;

namespace Cypress.Comps.PinsAndPorts.cy_pins_v2_20
{
    public partial class CyGeneralControl : UserControl
    {
        public delegate void PinTypeChanged(CyPinType pinType, IList<CyPinData.PerPin> pins);

        public static readonly CyPinData.ErrorMgrKey[] OwnedSettings = new CyPinData.ErrorMgrKey[]
        {
            CyPinData.ErrorMgrKey.TYPE_IS_ANALOG,
            CyPinData.ErrorMgrKey.TYPE_IS_DIGITAL_IN,
            CyPinData.ErrorMgrKey.TYPE_IS_DIGITAL_IN_HW,
            CyPinData.ErrorMgrKey.TYPE_IS_DIGITAL_OUT,
            CyPinData.ErrorMgrKey.TYPE_IS_DIGITAL_OUT_HW,
            CyPinData.ErrorMgrKey.TYPE_IS_DIGITAL_OUT_OE,
            CyPinData.ErrorMgrKey.TYPE_IS_BIDIRECTIONAL,
            CyPinData.ErrorMgrKey.TYPE_SHOW_EXTERNAL_TERM,
            CyPinData.ErrorMgrKey.GENERAL_DRIVE_MODE,
            CyPinData.ErrorMgrKey.GENERAL_INITIAL_STATE,
            CyPinData.ErrorMgrKey.GENERAL_MINIMUM_SUPPLY,
            CyPinData.ErrorMgrKey.GENERAL_TYPE,
        };

        private IList<CyPinData.PerPin> m_pins;
        private readonly PinTypeChanged m_pinTypeChanged;
        private readonly CyPerPinDataControl.SIOStateChangedHandler m_onSIOStateChanged;
        // Appears in CyPinControl, but GeneralControl has all the info required to update it
        private readonly CyPinPicture m_pinPicture;
        private readonly bool m_isSysBuilder;
        CyDeviceSupport m_deviceSupport;

        public CyGeneralControl( CyDeviceSupport deviceSupport, CyErrorManager errMgr, CyPinData pins, 
                               PinTypeChanged pinTypeChanged, CyPerPinDataControl.SIOStateChangedHandler sioStateChanged,
                               CyPinPicture pinPicture, bool isSysBuilder)
        {
            InitializeComponent();
            m_deviceSupport = deviceSupport;
            m_isSysBuilder = isSysBuilder;
            m_pins = pins.Pins;

            m_onSIOStateChanged = sioStateChanged;
            m_pinPicture = pinPicture;
            m_pinTypeChanged = pinTypeChanged;

            bool showAnalog = !deviceSupport.HasData || !deviceSupport.IsTSG4;
            bool showHotSwap = !deviceSupport.HasData || deviceSupport.HasSIO || deviceSupport.HasOVT;
            // Bypass the normal rules for showing analog/hotswap if we already have a pin which uses one of them
            foreach (CyPinData.PerPin pin in pins.Pins)
            {
                showAnalog |= ((pin.Type & CyPinType.ANALOG) == CyPinType.ANALOG);
                showHotSwap |= pin.GeneralHotSwap;
            }

            m_analogCheckBox.Visible = showAnalog;
            m_hotSwapCheckBox.Visible &= showHotSwap;

            if (isSysBuilder)
            {
                // In system builder, hide the checkboxes for analog, external terminal, and any of the hw connections
                m_displayDigitalInputCheckBox.Visible = m_displayDigitalOutputCheckBox.Visible =
                    m_analogCheckBox.Visible = m_annotCheckBox.Visible = m_displayDigitalOutputCheckBox.Visible = 
                    m_displayDigitalInputCheckBox.Visible = m_oeCheckBox.Visible = false;
                m_displayDigitalInputCheckBox.CheckState = m_displayDigitalOutputCheckBox.CheckState =
                    m_analogCheckBox.CheckState = m_annotCheckBox.CheckState = CheckState.Unchecked;
                // Propogate to the pin as well so we still work when copy-pasted to the schematic
                foreach (CyPinData.PerPin pin in pins.Pins)
                    pin.TypeIsDigitalOutputHw = pin.TypeIsDigitalInputHw = false;
            }

            EnableEvents();

            errMgr.RegisterSettingOwner(CyPinData.ErrorMgrKey.TYPE_IS_ANALOG, m_errorProvider, m_analogCheckBox);
            errMgr.RegisterSettingOwner(CyPinData.ErrorMgrKey.TYPE_IS_DIGITAL_IN, m_errorProvider, m_digInputCheckBox);
            errMgr.RegisterSettingOwner(CyPinData.ErrorMgrKey.TYPE_IS_DIGITAL_IN_HW, m_errorProvider, m_displayDigitalInputCheckBox);
            errMgr.RegisterSettingOwner(CyPinData.ErrorMgrKey.TYPE_IS_DIGITAL_OUT, m_errorProvider, m_digOutputCheckBox);
            errMgr.RegisterSettingOwner(CyPinData.ErrorMgrKey.TYPE_IS_DIGITAL_OUT_HW, m_errorProvider, m_displayDigitalOutputCheckBox);
            errMgr.RegisterSettingOwner(CyPinData.ErrorMgrKey.TYPE_IS_DIGITAL_OUT_OE, m_errorProvider, m_oeCheckBox);
            errMgr.RegisterSettingOwner(CyPinData.ErrorMgrKey.TYPE_IS_BIDIRECTIONAL, m_errorProvider, m_bidirCheckBox);
            errMgr.RegisterSettingOwner(CyPinData.ErrorMgrKey.TYPE_SHOW_EXTERNAL_TERM, m_errorProvider, m_annotCheckBox);
            errMgr.RegisterSettingOwner(CyPinData.ErrorMgrKey.GENERAL_DRIVE_MODE, m_errorProvider, m_driveModeComboBox);
            errMgr.RegisterSettingOwner(CyPinData.ErrorMgrKey.GENERAL_INITIAL_STATE, m_errorProvider, m_initStateComboBox);
            errMgr.RegisterSettingOwner(CyPinData.ErrorMgrKey.GENERAL_MINIMUM_SUPPLY, m_errorProvider, m_supplyVoltageTextBox);
            errMgr.RegisterSettingOwner(CyPinData.ErrorMgrKey.GENERAL_TYPE, m_errorProvider, m_connectivityGroupBox);
            errMgr.RegisterSettingOwner(CyPinData.ErrorMgrKey.INPUT_HOT_SWAP, m_errorProvider, m_hotSwapCheckBox);

            #region Drive mode

            m_driveModePictureBox.SizeMode = PictureBoxSizeMode.Zoom;

            m_driveModeComboBox.DropDownStyle = ComboBoxStyle.DropDownList;
            m_driveModeComboBox.Items.Add(
                new CyComboItem<CyDriveMode>(CyDriveMode.STRONG_DRIVE, "Strong drive"));
            m_driveModeComboBox.Items.Add(
                new CyComboItem<CyDriveMode>(CyDriveMode.OPEN_DRAIN_DRIVE_HIGH, "Open drain, drives high"));
            m_driveModeComboBox.Items.Add(
                new CyComboItem<CyDriveMode>(CyDriveMode.OPEN_DRAIN_DRIVE_LOW, "Open drain, drives low"));
            m_driveModeComboBox.Items.Add(
                new CyComboItem<CyDriveMode>(CyDriveMode.RESISTIVE_PULL_UP, "Resistive pull up"));
            m_driveModeComboBox.Items.Add(
                new CyComboItem<CyDriveMode>(CyDriveMode.RESISTIVE_PULL_DOWN, "Resistive pull down"));
            m_driveModeComboBox.Items.Add(
                new CyComboItem<CyDriveMode>(CyDriveMode.RESISTIVE_PULL_UP_DOWN, "Resistive pull up/down"));
            m_driveModeComboBox.Items.Add(
                new CyComboItem<CyDriveMode>(CyDriveMode.HIGH_IMPEDANCE_DIGITAL, "High impedance digital"));
            m_driveModeComboBox.Items.Add(
                new CyComboItem<CyDriveMode>(CyDriveMode.HIGH_IMPEDANCE_ANALOG, "High impedance analog"));

            UpdateDriveModeImage();

            m_initStateComboBox.DropDownStyle = ComboBoxStyle.DropDownList;
            m_initStateComboBox.Items.Add(new CyComboItem<int>(0, "Low (0)"));
            m_initStateComboBox.Items.Add(new CyComboItem<int>(1, "High (1)"));

            m_errorProvider.SetIconAlignment(m_connectivityGroupBox, ErrorIconAlignment.TopRight);
            m_errorProvider.SetIconPadding(m_connectivityGroupBox, -20); // Move to inside right of group box
            m_errorProvider.SetIconAlignment(m_hotSwapCheckBox, ErrorIconAlignment.MiddleRight);
            m_errorProvider.SetIconPadding(m_hotSwapCheckBox, 3);
            m_errorProvider.SetIconAlignment(m_initStateComboBox, ErrorIconAlignment.MiddleRight);
            m_errorProvider.SetIconAlignment(m_supplyVoltageTextBox, ErrorIconAlignment.MiddleRight);
            m_errorProvider.SetIconPadding(m_driveModeErrorLocLabel, 3);
            m_errorProvider.SetIconAlignment(m_driveModeErrorLocLabel, ErrorIconAlignment.MiddleRight);
            #endregion
        }

        private void EnableEvents()
        {
            m_analogCheckBox.CheckedChanged += m_analogCheckBox_CheckedChanged;
            m_hotSwapCheckBox.CheckedChanged += m_hotSwapCheckBox_CheckedChanged;
            m_digInputCheckBox.CheckedChanged += m_digInputCheckBox_CheckedChanged;
            m_displayDigitalInputCheckBox.CheckedChanged += m_displayDigitalInputCheckBox_CheckedChanged;
            m_digOutputCheckBox.CheckedChanged += m_digOutputCheckBox_CheckedChanged;
            m_displayDigitalOutputCheckBox.CheckedChanged += m_displayDigitalOutputCheckBox_CheckedChanged;
            m_oeCheckBox.CheckedChanged += m_oeCheckBox_CheckedChanged;
            m_bidirCheckBox.CheckedChanged += m_bidirCheckBox_CheckedChanged;
            m_annotCheckBox.CheckedChanged += m_annotCheckBox_CheckedChanged;
            m_initStateComboBox.SelectedIndexChanged += m_initStateComboBox_SelectedIndexChanged;
            m_supplyVoltageTextBox.Validated += m_supplyVoltageTextBox_Validated;
            m_supplyVoltageTextBox.Validating += m_supplyVoltageTextBox_Validating;
            m_driveModeComboBox.SelectedIndexChanged += m_driveModeComboBox_SelectedIndexChanged;
        }
        private void DisableEvents()
        {
            m_analogCheckBox.CheckedChanged -= m_analogCheckBox_CheckedChanged;
            m_hotSwapCheckBox.CheckedChanged -= m_hotSwapCheckBox_CheckedChanged;
            m_digInputCheckBox.CheckedChanged -= m_digInputCheckBox_CheckedChanged;
            m_displayDigitalInputCheckBox.CheckedChanged -= m_displayDigitalInputCheckBox_CheckedChanged;
            m_digOutputCheckBox.CheckedChanged -= m_digOutputCheckBox_CheckedChanged;
            m_displayDigitalOutputCheckBox.CheckedChanged -= m_displayDigitalOutputCheckBox_CheckedChanged;
            m_oeCheckBox.CheckedChanged -= m_oeCheckBox_CheckedChanged;
            m_bidirCheckBox.CheckedChanged -= m_bidirCheckBox_CheckedChanged;
            m_annotCheckBox.CheckedChanged -= m_annotCheckBox_CheckedChanged;
            m_initStateComboBox.SelectedIndexChanged -= m_initStateComboBox_SelectedIndexChanged;
            m_supplyVoltageTextBox.Validated -= m_supplyVoltageTextBox_Validated;
            m_supplyVoltageTextBox.Validating -= m_supplyVoltageTextBox_Validating;
            m_driveModeComboBox.SelectedIndexChanged -= m_driveModeComboBox_SelectedIndexChanged;
        }

        internal void UpdateData(IList<CyPinData.PerPin> pins)
        {
            m_pins = pins;
            UpdatePinType();
            UpdateDriveMode(); // Needs to be after UpdatePinType - drive mode may change based on pin type
        }

        private void UpdatePinType()
        {
            DisableEvents();
            CheckState analog = ((m_pins[0].Type & CyPinType.ANALOG) > 0) ? CheckState.Checked : CheckState.Unchecked;
            CheckState digIn = ((m_pins[0].Type & CyPinType.DIGITAL_IN) > 0) ? CheckState.Checked : CheckState.Unchecked;
            CheckState digInHw = m_pins[0].TypeIsDigitalInputHw ? CheckState.Checked : CheckState.Unchecked;
            CheckState digOut = ((m_pins[0].Type & CyPinType.DIGITAL_OUT) > 0) ? CheckState.Checked : CheckState.Unchecked;
            CheckState digOutHw = m_pins[0].TypeIsDigitalOutputHw ? CheckState.Checked : CheckState.Unchecked;
            CheckState digOE = ((m_pins[0].Type & CyPinType.OE) > 0) ? CheckState.Checked : CheckState.Unchecked;
            CheckState biDir = ((m_pins[0].Type & CyPinType.BIDIRECTIONAL) > 0) ? CheckState.Checked : CheckState.Unchecked;
            CheckState annot = m_pins[0].TypeShowExternalTerm ? CheckState.Checked : CheckState.Unchecked;
            CheckState hotSwap = m_pins[0].GeneralHotSwap ? CheckState.Checked : CheckState.Unchecked;

            for (int i = 1; i < m_pins.Count; i++)
            {
                if (analog != (((m_pins[i].Type & CyPinType.ANALOG) > 0) ? CheckState.Checked : CheckState.Unchecked))
                    analog = CheckState.Indeterminate;
                if (digIn != (((m_pins[i].Type & CyPinType.DIGITAL_IN) > 0) ? CheckState.Checked : CheckState.Unchecked))
                    digIn = CheckState.Indeterminate;
                if (digInHw != (m_pins[i].TypeIsDigitalInputHw ? CheckState.Checked : CheckState.Unchecked))
                    digInHw = CheckState.Indeterminate;
                if (digOut != (((m_pins[i].Type & CyPinType.DIGITAL_OUT) > 0) ? CheckState.Checked : CheckState.Unchecked))
                    digOut = CheckState.Indeterminate;
                if (digOutHw != (m_pins[i].TypeIsDigitalOutputHw ? CheckState.Checked : CheckState.Unchecked))
                    digOutHw = CheckState.Indeterminate;
                if (digOE != (((m_pins[i].Type & CyPinType.OE) > 0) ? CheckState.Checked : CheckState.Unchecked))
                    digOE = CheckState.Indeterminate;
                if (biDir != (((m_pins[i].Type & CyPinType.BIDIRECTIONAL) > 0) ? CheckState.Checked : CheckState.Unchecked))
                    biDir = CheckState.Indeterminate;
                if (annot != (m_pins[i].TypeShowExternalTerm ? CheckState.Checked : CheckState.Unchecked))
                    annot = CheckState.Indeterminate;
                if (hotSwap != (m_pins[i].GeneralHotSwap ? CheckState.Checked : CheckState.Unchecked))
                    hotSwap = CheckState.Indeterminate;
            }

            m_digInputCheckBox.CheckState = digIn;
            m_digOutputCheckBox.CheckState = digOut;
            m_oeCheckBox.CheckState = digOE;
            m_bidirCheckBox.CheckState = biDir;
            m_hotSwapCheckBox.CheckState = hotSwap;

            // The "HW terminal" checkboxes are ignored, disabled, and should stay unchecked in system builder
            if (!m_isSysBuilder)
            {
                m_analogCheckBox.CheckState = analog;
                m_displayDigitalInputCheckBox.CheckState = digInHw;
                m_displayDigitalOutputCheckBox.CheckState = digOutHw;
                m_annotCheckBox.CheckState = annot;
            }

            UpdateDigInSubCheckBoxEnabledState();
            UpdateDigOutSubCheckBoxEnabledState();
            UpdateHotSwapCheckBoxEnabledState();
            EnableEvents();
            UpdatePreviewPic();
        }

        private void UpdateDriveMode()
        {
            DisableEvents();
            int driveMode = Utils.GetIndex<CyDriveMode>(m_driveModeComboBox, m_pins[0].GeneralDriveMode);
            int state = Utils.GetIndex<int>(m_initStateComboBox, m_pins[0].GeneralInitialState ? 1 : 0);
            string supply = m_pins[0].GeneralMinimumSupply;
            bool multipleSupplySelections = false;

            for (int i = 1; i < m_pins.Count; i++)
            {
                if (driveMode != (Utils.GetIndex<CyDriveMode>(m_driveModeComboBox, m_pins[i].GeneralDriveMode)))
                    driveMode = -1;
                if (state != (Utils.GetIndex<int>(m_initStateComboBox, m_pins[i].GeneralInitialState ? 1 : 0)))
                    state = -1;
                if (supply != m_pins[i].GeneralMinimumSupply)
                    multipleSupplySelections = true;
            }

            m_driveModeComboBox.SelectedIndex = driveMode;
            m_initStateComboBox.SelectedIndex = state;
            m_supplyVoltageTextBox.Text = multipleSupplySelections ? CyPinData.MultipleIOVoltageValue : supply;

            if (m_deviceSupport.IsPSoC4) 
            {
                // If we are a digital output, gray out initial state as both Output and OE are controlled by the DSI. 
                bool enableInitialState = !IsDigitalHwOutput;
                m_initStateComboBox.Enabled = enableInitialState;
            }

            EnableEvents();
            UpdateDriveModeImage();
        }

        public bool IsDigitalHwOutput
        {
            get
            {
                return m_digOutputCheckBox.CheckState == CheckState.Checked &&
                       m_displayDigitalOutputCheckBox.CheckState == CheckState.Checked;
            }
        }

        public bool IsHwOutputEnable
        {
            get
            {
                return m_digOutputCheckBox.CheckState == CheckState.Checked &&
                       m_oeCheckBox.CheckState == CheckState.Checked;
            }
        }

        private void UpdateHwPinConfig(CheckBox chkBox, CyPinType pinType)
        {
            CyPinType newTypeOpts = 0;
            foreach (CyPinData.PerPin pin in m_pins)
            {
                if (chkBox.Checked)
                    pin.Type |= pinType;
                else
                    pin.Type &= ~pinType;

                newTypeOpts |= pin.Type;
            }
            UpdateDriveMode(); // Default changes based on pin type
            UpdatePreviewPic();
            m_pinTypeChanged(newTypeOpts, m_pins);
        }

        void m_analogCheckBox_CheckedChanged(object sender, EventArgs e)
        {
            UpdateHwPinConfig(m_analogCheckBox, CyPinType.ANALOG);
        }

        void m_digInputCheckBox_CheckedChanged(object sender, EventArgs e)
        {
            if (m_digInputCheckBox.Checked)
                m_bidirCheckBox.Checked = false;
            UpdateHwPinConfig(m_digInputCheckBox, CyPinType.DIGITAL_IN);
            UpdateDigInSubCheckBoxEnabledState();
        }

        void m_displayDigitalInputCheckBox_CheckedChanged(object sender, EventArgs e)
        {
            foreach (CyPinData.PerPin pin in m_pins)
                pin.TypeIsDigitalInputHw = m_displayDigitalInputCheckBox.Checked;
            UpdatePreviewPic();
            m_pinTypeChanged(CyPinType.DIGITAL_IN, m_pins);
        }

        void m_digOutputCheckBox_CheckedChanged(object sender, EventArgs e)
        {
            if (m_digOutputCheckBox.Checked)
                m_bidirCheckBox.Checked = false;
            UpdateHwPinConfig(m_digOutputCheckBox, CyPinType.DIGITAL_OUT);
            UpdateDigOutSubCheckBoxEnabledState();
        }

        void m_displayDigitalOutputCheckBox_CheckedChanged(object sender, EventArgs e)
        {
            foreach (CyPinData.PerPin pin in m_pins)
                pin.TypeIsDigitalOutputHw = m_displayDigitalOutputCheckBox.Checked;
            UpdateDriveMode(); // "Initial drive state" vs. "Initial output enable" may change
            UpdatePreviewPic();
        }

        void m_oeCheckBox_CheckedChanged(object sender, EventArgs e)
        {
            UpdateHwPinConfig(m_oeCheckBox, CyPinType.OE);
        }

        void m_bidirCheckBox_CheckedChanged(object sender, EventArgs e)
        {
            if (m_bidirCheckBox.Checked)
            {
                m_digInputCheckBox.Checked = false;
                m_digOutputCheckBox.Checked = false;
            }
            UpdateHwPinConfig(m_bidirCheckBox, CyPinType.BIDIRECTIONAL);
        }

        private void m_annotCheckBox_CheckedChanged(object sender, EventArgs e)
        {
            foreach (CyPinData.PerPin pin in m_pins)
                pin.TypeShowExternalTerm = m_annotCheckBox.Checked;
            UpdatePreviewPic();
        }

        void UpdateDigOutSubCheckBoxEnabledState()
        {
            // Never enable the HW connection checkboxes if we're in system builder mode
            m_oeCheckBox.Enabled = m_digOutputCheckBox.Checked && !m_isSysBuilder;
            m_displayDigitalOutputCheckBox.Enabled = m_digOutputCheckBox.Checked && !m_isSysBuilder;
        }

        void UpdateDigInSubCheckBoxEnabledState()
        {
            // Never enable the HW connection checkbox if we're in system builder mode
            m_displayDigitalInputCheckBox.Enabled = m_digInputCheckBox.Checked && !m_isSysBuilder;
        }

        void UpdateHotSwapCheckBoxEnabledState()
        {
            bool foundDigital = false;
            bool foundHotSwap = false;
            foreach (CyPinData.PerPin pin in m_pins)
            {
                foundDigital |= ((pin.Type & (CyPinType.DIGITAL_IN | CyPinType.DIGITAL_OUT | CyPinType.BIDIRECTIONAL)) != 0);
                foundHotSwap |= pin.GeneralHotSwap;
            }

            // Hot swap is enabled according to different rules depending on the device capabilities
            // * If the device has SIO, Hot Swap is only enabled if we found digital
            // * If the device has OVT, Hot Swap is always enabled
            // * If we have neither OVT nor SIO, Hot Swap is never enabled
            // * If we found a pin with hotswap enabled already, enabled so that the user can uncheck it if necessary
            bool enableHotSwap = foundHotSwap;
            if(m_deviceSupport.HasSIO)
            {
                enableHotSwap |= foundDigital;
            }
            enableHotSwap |= m_deviceSupport.HasOVT;

            m_hotSwapCheckBox.Enabled = enableHotSwap;
        }

        void UpdatePreviewPic()
        {
            m_pinPicture.ShowAnalog = m_analogCheckBox.Checked;
            m_pinPicture.ShowDigitalInput = m_digInputCheckBox.Checked;
            m_pinPicture.ShowDigitalOutput = m_digOutputCheckBox.Checked;
            m_pinPicture.ShowBidirectional = m_bidirCheckBox.Checked;
            m_pinPicture.ShowOutputEnable = m_oeCheckBox.Checked;
            m_pinPicture.ShowDigitalInputConnection = m_displayDigitalInputCheckBox.Checked;
            m_pinPicture.ShowDigitalOutputConnection = m_displayDigitalOutputCheckBox.Checked;
            m_pinPicture.ShowAnnotation = m_annotCheckBox.Checked;
            m_pinPicture.Invalidate();
        }

        private void m_hotSwapCheckBox_CheckedChanged(object sender, EventArgs e)
        {
            foreach (CyPinData.PerPin pin in m_pins)
                pin.GeneralHotSwap = m_hotSwapCheckBox.Checked;
            m_onSIOStateChanged(); // Hot-swap can impact "SIO-ness"
        }

        #region Drive Mode

        void m_driveModeComboBox_SelectedIndexChanged(object sender, EventArgs e)
        {
            foreach (CyPinData.PerPin pin in m_pins)
            {
                pin.GeneralDriveMode = ((CyComboItem<CyDriveMode>)m_driveModeComboBox.SelectedItem).Item;

                if (m_deviceSupport.IsTSG4)
                    pin.InputBufferEnabled = (pin.GeneralDriveMode != CyDriveMode.HIGH_IMPEDANCE_ANALOG);
            }
            UpdateDriveMode(); // Changing drive mode may change initial state if the user hasn't explicitly set it
        }

        void m_supplyVoltageTextBox_Validating(object sender, CancelEventArgs e)
        {
            const string IO_VOLTAGE_NOT_NUMERIC = "Invalid supply voltage. Value must be numeric and non-negative";
            string supply = m_supplyVoltageTextBox.Text;
            // If empty or the pre-filled "multiple" value (which triggers no update), we're fine. 
            // Otherwise, must be numeric and non-negative
            if (!string.IsNullOrEmpty(supply) && supply != CyPinData.MultipleIOVoltageValue )
            {
                double tmp;
                if (!double.TryParse(supply, out tmp) || tmp < 0)
                {
                    e.Cancel = true;
                    MessageBox.Show(IO_VOLTAGE_NOT_NUMERIC, "Invalid supply voltage", MessageBoxButtons.OK, MessageBoxIcon.Error, MessageBoxDefaultButton.Button1);
                }
            }
        }

        void m_supplyVoltageTextBox_Validated(object sender, EventArgs e)
        {
            string supply = m_supplyVoltageTextBox.Text;
            if (supply != CyPinData.MultipleIOVoltageValue) // Leave each of the pins with its original value
            {
                foreach (CyPinData.PerPin pin in m_pins)
                    pin.GeneralMinimumSupply = m_supplyVoltageTextBox.Text;
            }
        }

        void m_initStateComboBox_SelectedIndexChanged(object sender, EventArgs e)
        {
            foreach (CyPinData.PerPin pin in m_pins)
                pin.GeneralInitialState = (((CyComboItem<int>)m_initStateComboBox.SelectedItem).Item == 1);
        }

        private void UpdateDriveModeImage()
        {
            if (m_driveModeComboBox.SelectedIndex < 0)
            {
                m_driveModePictureBox.Image = null;
            }
            else
            {
                CyDriveMode driveMode = ((CyComboItem<CyDriveMode>)m_driveModeComboBox.SelectedItem).Item;
                switch (driveMode)
                {
                    case CyDriveMode.STRONG_DRIVE:
                        using (MemoryStream ms = new MemoryStream(Resource1.StrongDriveEMF))
                            m_driveModePictureBox.Image = new Metafile(ms);
                        break;
                    case CyDriveMode.OPEN_DRAIN_DRIVE_LOW:
                        using (MemoryStream ms = new MemoryStream(Resource1.OpenDrainDrivesLowEMF))
                            m_driveModePictureBox.Image = new Metafile(ms);
                        break;
                    case CyDriveMode.OPEN_DRAIN_DRIVE_HIGH:
                        using (MemoryStream ms = new MemoryStream(Resource1.OpenDrainDrivesHighEMF))
                            m_driveModePictureBox.Image = new Metafile(ms);
                        break;
                    case CyDriveMode.RESISTIVE_PULL_UP:
                        using (MemoryStream ms = new MemoryStream(Resource1.ResPullUpEMF))
                            m_driveModePictureBox.Image = new Metafile(ms);
                        break;
                    case CyDriveMode.RESISTIVE_PULL_DOWN:
                        using (MemoryStream ms = new MemoryStream(Resource1.ResPullDownEMF))
                            m_driveModePictureBox.Image = new Metafile(ms);
                        break;
                    case CyDriveMode.RESISTIVE_PULL_UP_DOWN:
                        using (MemoryStream ms = new MemoryStream(Resource1.ResPullUpDownEMF))
                            m_driveModePictureBox.Image = new Metafile(ms);
                        break;
                    case CyDriveMode.HIGH_IMPEDANCE_ANALOG:
                        using (MemoryStream ms = new MemoryStream(Resource1.HiImpedanceAnalogEMF))
                            m_driveModePictureBox.Image = new Metafile(ms);
                        break;
                    case CyDriveMode.HIGH_IMPEDANCE_DIGITAL:
                        using (MemoryStream ms = new MemoryStream(Resource1.HiImpedanceDigitalEMF))
                            m_driveModePictureBox.Image = new Metafile(ms);
                        break;
                    default:
                        Debug.Fail("unhndled");
                        m_driveModePictureBox.Image = null;
                        break;
                }
            }
        }
    #endregion
    }
}
