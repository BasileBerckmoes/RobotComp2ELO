/*******************************************************************************
* Copyright 2008-2013, Cypress Semiconductor Corporation.  All rights reserved.
* You may use this file only in accordance with the license, terms, conditions, 
* disclaimers, and limitations in the end user license agreement accompanying 
* the software package with which this file was provided.
********************************************************************************/

using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Drawing;
using System.Drawing.Imaging;
using System.Data;
using System.Text;
using System.Windows.Forms;
using System.Diagnostics;
using System.IO;

namespace Cypress.Comps.PinsAndPorts.cy_pins_v2_0
{
    public partial class CyGeneralControl : UserControl
    {
        public static readonly CyPinData.Key[] OwnedSettings = new CyPinData.Key[]
        {
            CyPinData.Key.GENERAL_DRIVE_MODE,
            CyPinData.Key.GENERAL_INITIAL_STATE,
            CyPinData.Key.GENERAL_MINIMUM_SUPPLY,
        };

        private readonly bool m_isTSG4;
        private IList<CyPinData.PerPin> m_pins;

        public CyGeneralControl(CyDeviceSupport deviceSupport, CyErrorManager errMgr)
        {
            InitializeComponent();

            m_isTSG4 = deviceSupport.IsTSG4;
            m_driveModePictureBox.SizeMode = PictureBoxSizeMode.Zoom;

            m_driveModeComboBox.DropDownStyle = ComboBoxStyle.DropDownList;
            m_driveModeComboBox.Items.Add(
                new CyComboItem<CyDriveMode>(CyDriveMode.STRONG_DRIVE, "Strong Drive"));
            m_driveModeComboBox.Items.Add(
                new CyComboItem<CyDriveMode>(CyDriveMode.OPEN_DRAIN_DRIVE_HIGH, "Open Drain, Drives High"));
            m_driveModeComboBox.Items.Add(
                new CyComboItem<CyDriveMode>(CyDriveMode.OPEN_DRAIN_DRIVE_LOW, "Open Drain, Drives Low"));
            m_driveModeComboBox.Items.Add(
                new CyComboItem<CyDriveMode>(CyDriveMode.RESISTIVE_PULL_UP, "Resistive Pull Up"));
            m_driveModeComboBox.Items.Add(
                new CyComboItem<CyDriveMode>(CyDriveMode.RESISTIVE_PULL_DOWN, "Resistive Pull Down"));
            m_driveModeComboBox.Items.Add(
                new CyComboItem<CyDriveMode>(CyDriveMode.RESISTIVE_PULL_UP_DOWN, "Resistive Pull Up/Down"));
            m_driveModeComboBox.Items.Add(
                new CyComboItem<CyDriveMode>(CyDriveMode.HIGH_IMPEDANCE_DIGITAL, "High Impedance Digital"));
            m_driveModeComboBox.Items.Add(
                new CyComboItem<CyDriveMode>(CyDriveMode.HIGH_IMPEDANCE_ANALOG, "High Impedance Analog"));

            UpdateDriveModeImage();

            m_initStateComboBox.DropDownStyle = ComboBoxStyle.DropDownList;
            m_initStateComboBox.Items.Add(new CyComboItem<int>(0, "Low (0)"));
            m_initStateComboBox.Items.Add(new CyComboItem<int>(1, "High (1)"));

            m_errorProvider.SetIconAlignment(m_initStateComboBox, ErrorIconAlignment.MiddleLeft);
            m_errorProvider.SetIconAlignment(m_supplyVoltageTextBox, ErrorIconAlignment.MiddleLeft);
            m_errorProvider.SetIconPadding(m_driveModeErrorLocLabel, 3);
            m_errorProvider.SetIconAlignment(m_driveModeErrorLocLabel, ErrorIconAlignment.MiddleRight);

            EnableEvents();

            errMgr.RegisterSettingOwner(CyPinData.Key.GENERAL_DRIVE_MODE, m_errorProvider, m_driveModeComboBox);
            errMgr.RegisterSettingOwner(CyPinData.Key.GENERAL_INITIAL_STATE, m_errorProvider, m_initStateComboBox);
            errMgr.RegisterSettingOwner(CyPinData.Key.GENERAL_MINIMUM_SUPPLY, m_errorProvider, m_supplyVoltageTextBox);
        }

        private void EnableEvents()
        {
            m_initStateComboBox.SelectedIndexChanged += m_initStateComboBox_SelectedIndexChanged;
            m_supplyVoltageTextBox.Validated += m_supplyVoltageTextBox_Validated;
            m_supplyVoltageTextBox.Validating += m_supplyVoltageTextBox_Validating;
            m_driveModeComboBox.SelectedIndexChanged += m_driveModeComboBox_SelectedIndexChanged;
        }
        private void DisableEvents()
        {
            m_initStateComboBox.SelectedIndexChanged -= m_initStateComboBox_SelectedIndexChanged;
            m_supplyVoltageTextBox.Validated -= m_supplyVoltageTextBox_Validated;
            m_supplyVoltageTextBox.Validating -= m_supplyVoltageTextBox_Validating;
            m_driveModeComboBox.SelectedIndexChanged -= m_driveModeComboBox_SelectedIndexChanged;
        }

        internal void UpdateData(IList<CyPinData.PerPin> pins)
        {
            m_pins = pins;

            int driveMode = Utils.GetIndex<CyDriveMode>(m_driveModeComboBox, pins[0].GeneralDriveMode);
            int state = Utils.GetIndex<int>(m_initStateComboBox, pins[0].GeneralInitialState ? 1 : 0);
            string supply = pins[0].GeneralMinimumSupply;
            bool supplyErr = false;

            for (int i = 1; i < pins.Count; i++)
            {
                if (driveMode != (Utils.GetIndex<CyDriveMode>(m_driveModeComboBox, pins[i].GeneralDriveMode)))
                    driveMode = -1;
                if (state != (Utils.GetIndex<int>(m_initStateComboBox, pins[i].GeneralInitialState ? 1 : 0)))
                    state = -1;
                if (supply != pins[i].GeneralMinimumSupply)
                    supplyErr = true;
            }

            DisableEvents();

            m_driveModeComboBox.SelectedIndex = driveMode;
            m_initStateComboBox.SelectedIndex = state;
            m_supplyVoltageTextBox.Text = supplyErr ? "" : supply.ToString();

            EnableEvents();
            UpdateDriveModeImage();
        }

        void m_driveModeComboBox_SelectedIndexChanged(object sender, EventArgs e)
        {
            foreach (CyPinData.PerPin pin in m_pins)
            {
                pin.GeneralDriveMode = ((CyComboItem<CyDriveMode>)m_driveModeComboBox.SelectedItem).Item;

                if (m_isTSG4)
                    pin.InputBufferEnabled = (pin.GeneralDriveMode != CyDriveMode.HIGH_IMPEDANCE_ANALOG);
            }
            UpdateData(m_pins); // Changing drive mode may change initial state if the user hasn't explicitly set it
            UpdateDriveModeImage();
        }

        const string IO_VOLTAGE_NOT_NUMERIC = "Invalid supply voltage. Value must be numeric and non-negative";
        void m_supplyVoltageTextBox_Validating(object sender, CancelEventArgs e)
        {
            string supply = m_supplyVoltageTextBox.Text;
            // If empty, we're fine. Otherwise, must be numeric and non-negative
            if (!string.IsNullOrEmpty(supply))
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
            foreach (CyPinData.PerPin pin in m_pins)
                pin.GeneralMinimumSupply = m_supplyVoltageTextBox.Text;
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
    }
}
