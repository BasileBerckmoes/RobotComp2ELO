/*******************************************************************************
* Copyright 2008-2016, Cypress Semiconductor Corporation.  All rights reserved.
* You may use this file only in accordance with the license, terms, conditions, 
* disclaimers, and limitations in the end user license agreement accompanying 
* the software package with which this file was provided.
********************************************************************************/

using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Diagnostics.CodeAnalysis;
using System.Drawing.Imaging;
using System.Windows.Forms;
using System.Diagnostics;
using System.IO;
using System.Linq;

namespace Cypress.Comps.PinsAndPorts.GPIO_PDL_v1_0
{
    [ExcludeFromCodeCoverage]
    public partial class CyGeneralControl : UserControl
    {
        internal static readonly Formal.ErrorKey[] OwnedSettings = new Formal.ErrorKey[]
        {
            Formal.ErrorKey.TYPE_IS_ANALOG,
            Formal.ErrorKey.TYPE_IS_DIGITAL_IN,
            Formal.ErrorKey.TYPE_IS_DIGITAL_IN_HW,
            Formal.ErrorKey.TYPE_IS_DIGITAL_OUT,
            Formal.ErrorKey.TYPE_IS_DIGITAL_OUT_HW,
            Formal.ErrorKey.TYPE_IS_DIGITAL_OUT_OE,
            Formal.ErrorKey.TYPE_IS_BIDIRECTIONAL,
            Formal.ErrorKey.TYPE_SHOW_EXTERNAL_TERM,
            Formal.ErrorKey.GENERAL_DRIVE_MODE,
            Formal.ErrorKey.GENERAL_INITIAL_STATE,
            Formal.ErrorKey.GENERAL_MINIMUM_SUPPLY,
            Formal.ErrorKey.GENERAL_TYPE,
        };

        private IList<CyPinData.PerPin> m_pins;
        private readonly Action<CyPinType, IList<CyPinData.PerPin>> m_pinTypeChanged;
        private readonly Action<IList<CyPinData.PerPin>> m_i2cFrequencyChanged;
        private readonly Action m_onSIOStateChanged;
        // Appears in CyPinControl, but GeneralControl has all the info required to update it
        private readonly CyPinPicture m_pinPicture;
        CyDeviceSupport m_deviceSupport;

        public CyGeneralControl(CyDeviceSupport deviceSupport, CyErrorManager errMgr, CyPinData pins,
                                CyPinPicture pinPicture, Action sioStateChanged,
                                Action<CyPinType, IList<CyPinData.PerPin>> pinTypeChanged,
                                Action<IList<CyPinData.PerPin>> i2cFrequencyChanged)
        {
            InitializeComponent();
            m_deviceSupport = deviceSupport;
            m_pins = pins.Pins;

            m_onSIOStateChanged = sioStateChanged;
            m_pinPicture = pinPicture;
            m_pinTypeChanged = pinTypeChanged;
            m_i2cFrequencyChanged = i2cFrequencyChanged;

            // Bypass the normal rules for showing analog/hotswap if we already have a pin which uses one of them
            m_hotSwapCheckBox.Visible &= deviceSupport.CanHotSwap(pins.Pins.Any(p => p.GeneralHotSwap), true);

            EnableEvents();

            errMgr.RegisterKeyOwner(Formal.ErrorKey.TYPE_IS_ANALOG, m_errorProvider, m_analogCheckBox);
            errMgr.RegisterKeyOwner(Formal.ErrorKey.TYPE_IS_DIGITAL_IN, m_errorProvider, m_digInputCheckBox);
            errMgr.RegisterKeyOwner(Formal.ErrorKey.TYPE_IS_DIGITAL_IN_HW, m_errorProvider, m_displayDigitalInputCheckBox);
            errMgr.RegisterKeyOwner(Formal.ErrorKey.TYPE_IS_DIGITAL_OUT, m_errorProvider, m_digOutputCheckBox);
            errMgr.RegisterKeyOwner(Formal.ErrorKey.TYPE_IS_DIGITAL_OUT_HW, m_errorProvider, m_displayDigitalOutputCheckBox);
            errMgr.RegisterKeyOwner(Formal.ErrorKey.TYPE_IS_DIGITAL_OUT_OE, m_errorProvider, m_oeCheckBox);
            errMgr.RegisterKeyOwner(Formal.ErrorKey.TYPE_IS_BIDIRECTIONAL, m_errorProvider, m_bidirCheckBox);
            errMgr.RegisterKeyOwner(Formal.ErrorKey.TYPE_SHOW_EXTERNAL_TERM, m_errorProvider, m_annotCheckBox);
            errMgr.RegisterKeyOwner(Formal.ErrorKey.GENERAL_DRIVE_MODE, m_errorProvider, m_driveModeComboBox);
            errMgr.RegisterKeyOwner(Formal.ErrorKey.GENERAL_INITIAL_STATE, m_errorProvider, m_initStateComboBox);
            errMgr.RegisterKeyOwner(Formal.ErrorKey.GENERAL_MINIMUM_SUPPLY, m_errorProvider, m_supplyVoltageTextBox);
            errMgr.RegisterKeyOwner(Formal.ErrorKey.GENERAL_TYPE, m_errorProvider, m_connectivityGroupBox);
            errMgr.RegisterKeyOwner(Formal.ErrorKey.INPUT_HOT_SWAP, m_errorProvider, m_hotSwapCheckBox);
            errMgr.RegisterKeyOwner(Formal.ErrorKey.GENERAL_MAX_FREQUENCY, m_errorProvider, m_maxFrequencyComboBox);

            #region Drive mode

            m_driveModePictureBox.SizeMode = PictureBoxSizeMode.Zoom;

            m_driveModeComboBox.AddItem(CyDriveMode.Strong_Drive, Resource1.StrongDrive);
            m_driveModeComboBox.AddItem(CyDriveMode.Open_drain_Drive_high, Resource1.OpenDrainDrivesHigh);
            m_driveModeComboBox.AddItem(CyDriveMode.Open_drain_Drive_low, Resource1.OpenDrainDrivesLow);
            m_driveModeComboBox.AddItem(CyDriveMode.Resistive_pull_up, Resource1.ResPullUp);
            m_driveModeComboBox.AddItem(CyDriveMode.Resistive_pull_down, Resource1.ResPullDown);
            m_driveModeComboBox.AddItem(CyDriveMode.Resistive_pull_up_down, Resource1.ResPullUpDown);
            m_driveModeComboBox.AddItem(CyDriveMode.High_impedance_digital, Resource1.HighImpedanceDigital);
            m_driveModeComboBox.AddItem(CyDriveMode.High_impedance_analog, Resource1.HighImpedanceAnalog);

            UpdateDriveModeImage();

            m_initStateComboBox.AddItem(0, Resource1.Low + " (" + Formal.Low + ")");
            m_initStateComboBox.AddItem(1, Resource1.High + " (" + Formal.High + ")");

            IEnumerable<CyMaxFrequency> maxFreqs = deviceSupport.AvailableFrequencies;
            IEnumerable<CyI2CMode> i2cModes = deviceSupport.AvailableI2CModes;

            Action<CyMaxFrequency> AddFrequency = freq =>
                {
                    if (maxFreqs.Contains(freq) || pins.Pins.Any(p => p.MaxFrequency == freq))
                        m_maxFrequencyComboBox.AddItem(freq, string.Format(Resource1.Prompt_MHz, Formal.AsString(freq)));
                };
            Action<CyI2CMode, string> AddI2C = (mode, descr) =>
                {
                    if (i2cModes.Contains(mode) || pins.Pins.Any(p => p.I2CMode == mode))
                        m_maxFrequencyComboBox.AddItem(mode, descr);
                };
            AddFrequency(CyMaxFrequency.MHz_200);
            AddFrequency(CyMaxFrequency.MHz_100);
            AddFrequency(CyMaxFrequency.MHz_80);
            AddFrequency(CyMaxFrequency.MHz_50);
            AddFrequency(CyMaxFrequency.MHz_1);
            AddI2C(CyI2CMode.I2C_SM, Formal.PrettyString(CyI2CMode.I2C_SM));
            AddI2C(CyI2CMode.I2C_FM, Formal.PrettyString(CyI2CMode.I2C_FM));
            AddI2C(CyI2CMode.I2C_FM_plus, Formal.PrettyString(CyI2CMode.I2C_FM_plus));
            AddI2C(CyI2CMode.I2C_HS, Formal.PrettyString(CyI2CMode.I2C_HS));

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
            m_driveModeComboBox.SelectedIndexChanged += m_driveModeComboBox_SelectedIndexChanged;
            m_initStateComboBox.SelectedIndexChanged += m_initStateComboBox_SelectedIndexChanged;
            m_supplyVoltageTextBox.Validated += m_supplyVoltageTextBox_Validated;
            m_supplyVoltageTextBox.Validating += m_supplyVoltageTextBox_Validating;
            m_maxFrequencyComboBox.SelectedIndexChanged += m_maxFrequencyComboBox_SelectedIndexChanged;
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
            m_driveModeComboBox.SelectedIndexChanged -= m_driveModeComboBox_SelectedIndexChanged;
            m_initStateComboBox.SelectedIndexChanged -= m_initStateComboBox_SelectedIndexChanged;
            m_supplyVoltageTextBox.Validated -= m_supplyVoltageTextBox_Validated;
            m_supplyVoltageTextBox.Validating -= m_supplyVoltageTextBox_Validating;
            m_maxFrequencyComboBox.SelectedIndexChanged -= m_maxFrequencyComboBox_SelectedIndexChanged;
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
            CheckState analog = m_pins[0].Type.Is(CyPinType.Analog) ? CheckState.Checked : CheckState.Unchecked;
            CheckState digIn = m_pins[0].Type.Is(CyPinType.Digital_In) ? CheckState.Checked : CheckState.Unchecked;
            CheckState digInHw = m_pins[0].TypeIsDigitalInputHw ? CheckState.Checked : CheckState.Unchecked;
            CheckState digOut = m_pins[0].Type.Is(CyPinType.Digital_Out) ? CheckState.Checked : CheckState.Unchecked;
            CheckState digOutHw = m_pins[0].TypeIsDigitalOutputHw ? CheckState.Checked : CheckState.Unchecked;
            CheckState digOE = m_pins[0].Type.Is(CyPinType.OE) ? CheckState.Checked : CheckState.Unchecked;
            CheckState biDir = m_pins[0].Type.Is(CyPinType.Bidirectional) ? CheckState.Checked : CheckState.Unchecked;
            CheckState annot = m_pins[0].TypeShowExternalTerm ? CheckState.Checked : CheckState.Unchecked;
            CheckState hotSwap = m_pins[0].GeneralHotSwap ? CheckState.Checked : CheckState.Unchecked;

            foreach (CyPinData.PerPin pin in m_pins.Skip(1))
            {
                if (analog != (pin.Type.Is(CyPinType.Analog) ? CheckState.Checked : CheckState.Unchecked))
                    analog = CheckState.Indeterminate;
                if (digIn != (pin.Type.Is(CyPinType.Digital_In) ? CheckState.Checked : CheckState.Unchecked))
                    digIn = CheckState.Indeterminate;
                if (digInHw != (pin.TypeIsDigitalInputHw ? CheckState.Checked : CheckState.Unchecked))
                    digInHw = CheckState.Indeterminate;
                if (digOut != (pin.Type.Is(CyPinType.Digital_Out) ? CheckState.Checked : CheckState.Unchecked))
                    digOut = CheckState.Indeterminate;
                if (digOutHw != (pin.TypeIsDigitalOutputHw ? CheckState.Checked : CheckState.Unchecked))
                    digOutHw = CheckState.Indeterminate;
                if (digOE != (pin.Type.Is(CyPinType.OE) ? CheckState.Checked : CheckState.Unchecked))
                    digOE = CheckState.Indeterminate;
                if (biDir != (pin.Type.Is(CyPinType.Bidirectional) ? CheckState.Checked : CheckState.Unchecked))
                    biDir = CheckState.Indeterminate;
                if (annot != (pin.TypeShowExternalTerm ? CheckState.Checked : CheckState.Unchecked))
                    annot = CheckState.Indeterminate;
                if (hotSwap != (pin.GeneralHotSwap ? CheckState.Checked : CheckState.Unchecked))
                    hotSwap = CheckState.Indeterminate;
            }

            m_digInputCheckBox.CheckState = digIn;
            m_digOutputCheckBox.CheckState = digOut;
            m_oeCheckBox.CheckState = digOE;
            m_bidirCheckBox.CheckState = biDir;
            m_hotSwapCheckBox.CheckState = hotSwap;
            m_analogCheckBox.CheckState = analog;
            m_displayDigitalInputCheckBox.CheckState = digInHw;
            m_displayDigitalOutputCheckBox.CheckState = digOutHw;
            m_annotCheckBox.CheckState = annot;

            UpdateDigInSubCheckBoxEnabledState();
            UpdateDigOutSubCheckBoxEnabledState();
            UpdateHotSwapCheckBoxEnabledState();
            EnableEvents();
            UpdatePreviewPic();
        }

        private void UpdateDriveMode()
        {
            DisableEvents();
            int driveMode = m_driveModeComboBox.GetIndex(m_pins[0].GeneralDriveMode);
            int state = m_initStateComboBox.GetIndex(m_pins[0].GeneralInitialState ? 1 : 0);
            int freq = GetFrequencyIndex(m_pins[0]);
            string supply = m_pins[0].GeneralMinimumSupply;
            bool multipleSupplySelections = false;

            foreach (CyPinData.PerPin pin in m_pins.Skip(1))
            {
                if (driveMode != m_driveModeComboBox.GetIndex(pin.GeneralDriveMode))
                    driveMode = -1;
                if (state != m_initStateComboBox.GetIndex(pin.GeneralInitialState ? 1 : 0))
                    state = -1;
                if (supply != pin.GeneralMinimumSupply)
                    multipleSupplySelections = true;
                if (freq != GetFrequencyIndex(pin))
                    freq = -1;
            }

            m_driveModeComboBox.SelectedIndex = driveMode;
            m_initStateComboBox.SelectedIndex = state;
            m_maxFrequencyComboBox.SelectedIndex = freq;
            m_supplyVoltageTextBox.Text = multipleSupplySelections ? Formal.IOVoltage_Multiple : supply;

            // If we are a digital output, gray out initial state as both Output and OE are controlled by the DSI. 
            m_initStateComboBox.Enabled = !IsDigitalHwOutput;

            EnableEvents();
            UpdateDriveModeImage();
        }

        private int GetFrequencyIndex(CyPinData.PerPin pin)
        {
            for (int i = 0; i < m_maxFrequencyComboBox.Items.Count; i++)
            {
                CyComboItem<CyMaxFrequency> itemF = m_maxFrequencyComboBox.Items[i] as CyComboItem<CyMaxFrequency>;
                if (null != itemF)
                {
                    if (itemF.Item == pin.MaxFrequency)
                        return i;
                }
                else
                {
                    CyComboItem<CyI2CMode> itemI = m_maxFrequencyComboBox.Items[i] as CyComboItem<CyI2CMode>;
                    if (null != itemI)
                    {
                        if (itemI.Item == pin.I2CMode)
                            return i;
                    }
                    else
                        Debug.Fail("Invalid combo box frequency");
                }
            }
            return -1;
        }

        public bool IsDigitalHwOutput
        {
            get
            {
                return m_digOutputCheckBox.CheckState == CheckState.Checked &&
                       m_displayDigitalOutputCheckBox.CheckState == CheckState.Checked;
            }
        }

        private void UpdateHwPinConfig(CyPinType pinType, bool isSet)
        {
            CyPinType newTypeOpts = 0;
            foreach (CyPinData.PerPin pin in m_pins)
            {
                if (isSet)
                    pin.Type |= pinType;
                else
                    pin.Type &= ~pinType;

                newTypeOpts |= pin.Type;
            }
            if (CyPinType.None != pinType)
                UpdateDriveMode(); // Default changes based on pin type
            UpdatePreviewPic();
            m_pinTypeChanged(newTypeOpts, m_pins);
        }

        void m_analogCheckBox_CheckedChanged(object sender, EventArgs e)
        {
            UpdateHwPinConfig(CyPinType.Analog, m_analogCheckBox.Checked);
        }

        void m_digInputCheckBox_CheckedChanged(object sender, EventArgs e)
        {
            if (m_digInputCheckBox.Checked)
                m_bidirCheckBox.Checked = false;
            UpdateHwPinConfig(CyPinType.Digital_In, m_digInputCheckBox.Checked);
            UpdateDigInSubCheckBoxEnabledState();
        }

        void m_displayDigitalInputCheckBox_CheckedChanged(object sender, EventArgs e)
        {
            foreach (CyPinData.PerPin pin in m_pins)
                pin.TypeIsDigitalInputHw = m_displayDigitalInputCheckBox.Checked;
            UpdateHwPinConfig(CyPinType.None, m_displayDigitalInputCheckBox.Checked);
        }

        void m_digOutputCheckBox_CheckedChanged(object sender, EventArgs e)
        {
            if (m_digOutputCheckBox.Checked)
                m_bidirCheckBox.Checked = false;

            // If DigOut changes when OE is set, change pin's OE setting to match DigOut
            if (m_oeCheckBox.Checked)
                UpdateHwPinConfig(CyPinType.OE, m_digOutputCheckBox.Checked);

            UpdateHwPinConfig(CyPinType.Digital_Out, m_digOutputCheckBox.Checked);
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
            UpdateHwPinConfig(CyPinType.OE, m_oeCheckBox.Checked);
        }

        void m_bidirCheckBox_CheckedChanged(object sender, EventArgs e)
        {
            if (m_bidirCheckBox.Checked)
            {
                m_digInputCheckBox.Checked = false;
                m_digOutputCheckBox.Checked = false;
            }
            UpdateHwPinConfig(CyPinType.Bidirectional, m_bidirCheckBox.Checked);
        }

        private void m_annotCheckBox_CheckedChanged(object sender, EventArgs e)
        {
            foreach (CyPinData.PerPin pin in m_pins)
                pin.TypeShowExternalTerm = m_annotCheckBox.Checked;
            UpdatePreviewPic();
        }

        void UpdateDigOutSubCheckBoxEnabledState()
        {
            m_oeCheckBox.Enabled = m_digOutputCheckBox.Checked;
            m_displayDigitalOutputCheckBox.Enabled = m_digOutputCheckBox.Checked;
        }

        void UpdateDigInSubCheckBoxEnabledState()
        {
            m_displayDigitalInputCheckBox.Enabled = m_digInputCheckBox.Checked;
        }

        void UpdateHotSwapCheckBoxEnabledState()
        {
            bool anyHotSwap = m_pins.Any(pin => pin.GeneralHotSwap);
            bool anyDigital = m_pins.Any(pin => pin.Type != CyPinType.Analog);
            m_hotSwapCheckBox.Enabled = m_deviceSupport.CanHotSwap(anyHotSwap, anyDigital);
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
            }
            UpdateDriveMode(); // Changing drive mode may change initial state if the user hasn't explicitly set it
        }

        void m_supplyVoltageTextBox_Validating(object sender, CancelEventArgs e)
        {
            string supply = m_supplyVoltageTextBox.Text;
            // If empty or the pre-filled "multiple" value (which triggers no update), we're fine. 
            // Otherwise, must be numeric and non-negative
            if (!string.IsNullOrEmpty(supply) && supply != Formal.IOVoltage_Multiple)
            {
                double tmp;
                if (!double.TryParse(supply, out tmp) || tmp < 0)
                {
                    e.Cancel = true;
                    MessageBox.Show(Resource1.Msg_InvalidSupplyVoltage_numeric, Resource1.Msg_InvalidSupplyVoltage,
                        MessageBoxButtons.OK, MessageBoxIcon.Error, MessageBoxDefaultButton.Button1);
                }
            }
        }

        void m_supplyVoltageTextBox_Validated(object sender, EventArgs e)
        {
            string supply = m_supplyVoltageTextBox.Text;
            if (supply != Formal.IOVoltage_Multiple) // Leave each of the pins with its original value
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

        void m_maxFrequencyComboBox_SelectedIndexChanged(object sender, EventArgs e)
        {
            foreach (CyPinData.PerPin pin in m_pins)
            {
                CyComboItem<CyMaxFrequency> itemF = m_maxFrequencyComboBox.SelectedItem as CyComboItem<CyMaxFrequency>;
                if (null != itemF)
                {
                    pin.MaxFrequency = itemF.Item;
                    pin.I2CMode = CyI2CMode.I2C_NA;
                }
                else
                {
                    CyComboItem<CyI2CMode> itemI = m_maxFrequencyComboBox.SelectedItem as CyComboItem<CyI2CMode>;
                    if (null != itemI)
                    {
                        pin.MaxFrequency = CyMaxFrequency.MHz_NA;
                        pin.I2CMode = itemI.Item;
                    }
                    else
                        Debug.Fail("Invalid combo box frequency");
                }
            }
            m_i2cFrequencyChanged(m_pins);
        }

        private void UpdateDriveModeImage()
        {
            if (m_driveModeComboBox.SelectedIndex < 0)
            {
                m_driveModePictureBox.Image = null;
            }
            else
            {
                bool isInput = m_digInputCheckBox.Checked || m_bidirCheckBox.Checked;
                byte[] res;
                CyDriveMode driveMode = ((CyComboItem<CyDriveMode>)m_driveModeComboBox.SelectedItem).Item;
                switch (driveMode)
                {
                    case CyDriveMode.Strong_Drive:
                        res = isInput ? Resource1.StrongDriveEMF : Resource1.StrongDriveInpDisEMF;
                        using (MemoryStream ms = new MemoryStream(res))
                            m_driveModePictureBox.Image = new Metafile(ms);
                        break;
                    case CyDriveMode.Open_drain_Drive_low:
                        res = isInput ? Resource1.OpenDrainDrivesLowEMF : Resource1.OpenDrainDrivesLowInpDisEMF;
                        using (MemoryStream ms = new MemoryStream(res))
                            m_driveModePictureBox.Image = new Metafile(ms);
                        break;
                    case CyDriveMode.Open_drain_Drive_high:
                        res = isInput ? Resource1.OpenDrainDrivesHighEMF : Resource1.OpenDrainDrivesHighInpDisEMF;
                        using (MemoryStream ms = new MemoryStream(res))
                            m_driveModePictureBox.Image = new Metafile(ms);
                        break;
                    case CyDriveMode.Resistive_pull_up:
                        res = isInput ? Resource1.ResPullUpEMF : Resource1.ResPullUpInpDisEMF;
                        using (MemoryStream ms = new MemoryStream(res))
                            m_driveModePictureBox.Image = new Metafile(ms);
                        break;
                    case CyDriveMode.Resistive_pull_down:
                        res = isInput ? Resource1.ResPullDownEMF : Resource1.ResPullDownInpDisEMF;
                        using (MemoryStream ms = new MemoryStream(res))
                            m_driveModePictureBox.Image = new Metafile(ms);
                        break;
                    case CyDriveMode.Resistive_pull_up_down:
                        res = isInput ? Resource1.ResPullUpDownEMF : Resource1.ResPullUpDownInpDisEMF;
                        using (MemoryStream ms = new MemoryStream(res))
                            m_driveModePictureBox.Image = new Metafile(ms);
                        break;
                    case CyDriveMode.High_impedance_analog:
                        using (MemoryStream ms = new MemoryStream(Resource1.HiImpedanceAnalogEMF))
                            m_driveModePictureBox.Image = new Metafile(ms);
                        break;
                    case CyDriveMode.High_impedance_digital:
                        res = isInput ? Resource1.HiImpedanceDigitalEMF : Resource1.HiImpedanceDigitalInpDisEMF;
                        using (MemoryStream ms = new MemoryStream(res))
                            m_driveModePictureBox.Image = new Metafile(ms);
                        break;
                    default:
                        Debug.Fail("unhandled");
                        m_driveModePictureBox.Image = null;
                        break;
                }
            }
        }
        #endregion
    }
}
