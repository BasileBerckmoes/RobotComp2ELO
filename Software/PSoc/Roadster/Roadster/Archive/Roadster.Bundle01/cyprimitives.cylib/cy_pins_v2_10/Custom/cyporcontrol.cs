/*******************************************************************************
* Copyright 2008-2013, Cypress Semiconductor Corporation.  All rights reserved.
* You may use this file only in accordance with the license, terms, conditions, 
* disclaimers, and limitations in the end user license agreement accompanying 
* the software package with which this file was provided.
********************************************************************************/

using System;
using System.Collections.Generic;
using System.Windows.Forms;
using System.Diagnostics;

using CyDesigner.Extensions.Common;
using CyDesigner.Extensions.Gde;

namespace Cypress.Comps.PinsAndPorts.cy_pins_v2_10
{
    public partial class CyPORControl : UserControl, ICyParamEditingControl
    {
        public static readonly CyPinData.ErrorMgrKey[] OwnedSettings = new CyPinData.ErrorMgrKey[]
        {
            CyPinData.ErrorMgrKey.POWER_ON_RESET,
        };

        private readonly CyPinData m_pins;
        private readonly CyErrorManager m_errMgr;

        public CyPORControl(CyDeviceSupport deviceSupport, CyErrorManager errMgr, CyPinData pins)
        {
            InitializeComponent();

            m_pins = pins;
            m_errMgr = errMgr;
            Dock = DockStyle.Fill;

            m_porComboBox.DropDownStyle = ComboBoxStyle.DropDownList;
            m_porComboBox.Items.Add(
                new CyComboItem<CyPowerOnRestMode>(CyPowerOnRestMode.UNSPECIFIED, "Don't Care"));
            m_porComboBox.Items.Add(
                new CyComboItem<CyPowerOnRestMode>(CyPowerOnRestMode.HIZ_ANALOG, "High-Z Analog"));
            m_porComboBox.Items.Add(
                new CyComboItem<CyPowerOnRestMode>(CyPowerOnRestMode.PULLED_UP, "Pulled-Up"));
            m_porComboBox.Items.Add(
                new CyComboItem<CyPowerOnRestMode>(CyPowerOnRestMode.PULLED_DOWN, "Pulled-Down"));

            UpdateData();

            m_porComboBox.SelectedIndexChanged += new EventHandler(m_porComboBox_SelectedIndexChanged);

            errMgr.RegisterSettingOwner(CyPinData.ErrorMgrKey.POWER_ON_RESET, m_errorProvider, m_porComboBox);
        }

        internal void UpdateData()
        {
            m_porComboBox.SelectedIndex = Utils.GetIndex<CyPowerOnRestMode>(m_porComboBox, m_pins.PowerOnReset);
        }

        void m_porComboBox_SelectedIndexChanged(object sender, EventArgs e)
        {
            m_pins.PowerOnReset = ((CyComboItem<CyPowerOnRestMode>)m_porComboBox.SelectedItem).Item;
        }

        #region ICyParamEditingControl Members

        public Control DisplayControl
        {
            get { return this; }
        }

        public IEnumerable<CyCustErr> GetErrors()
        {
            foreach (string errMsg in m_errMgr.GetErrors(OwnedSettings))
                yield return new CyCustErr(errMsg);
        }

        #endregion
    }
}
