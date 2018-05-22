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
using System.Data;
using System.Text;
using System.Windows.Forms;

using CyDesigner.Extensions.Common;
using CyDesigner.Extensions.Gde;

namespace Cypress.Comps.PinsAndPorts.cy_pins_v2_0
{
    public partial class CyMappingControl : UserControl, ICyParamEditingControl
    {
        public static readonly CyPinData.Key[] OwnedSettings = new CyPinData.Key[]
        {
            CyPinData.Key.MAPPING_DISPLAY_AS_BUS,
            CyPinData.Key.MAPPING_CONTIGIOUS,
            CyPinData.Key.MAPPING_SPANNING,
        };

        private readonly CyPinData m_pins;
        private readonly CyErrorManager m_errMgr;

        public CyMappingControl(CyErrorManager errMgr, CyPinData pins)
        {
            InitializeComponent();

            m_pins = pins;
            m_errMgr = errMgr;
            Dock = DockStyle.Fill;
            m_spanningCheckBox.Enabled = false;

            UpdateData();

            m_displayAsBusCheckBox.CheckedChanged += m_displayAsBusCheckBox_CheckedChanged;
            m_contCheckBox.CheckedChanged += m_contCheckBox_CheckedChanged;
            m_spanningCheckBox.CheckedChanged += m_spanningCheckBox_CheckedChanged;

            errMgr.RegisterSettingOwner(CyPinData.Key.MAPPING_DISPLAY_AS_BUS, m_errorProvider, m_displayAsBusCheckBox);
            errMgr.RegisterSettingOwner(CyPinData.Key.MAPPING_CONTIGIOUS, m_errorProvider, m_contCheckBox);
            errMgr.RegisterSettingOwner(CyPinData.Key.MAPPING_SPANNING, m_errorProvider, m_spanningCheckBox);
        }

        internal void UpdateData()
        {
            m_displayAsBusCheckBox.Checked = m_pins.MappingDisplayAsBus;
            m_contCheckBox.Checked = m_pins.MappingContigious;
        }

        void m_contCheckBox_CheckedChanged(object sender, EventArgs e)
        {
            m_pins.MappingContigious = m_contCheckBox.Checked;
            m_spanningCheckBox.Checked = !m_contCheckBox.Checked;
        }

        void m_spanningCheckBox_CheckedChanged(object sender, EventArgs e)
        {
            m_pins.MappingSpanning = m_spanningCheckBox.Checked;
        }

        void m_displayAsBusCheckBox_CheckedChanged(object sender, EventArgs e)
        {
            m_pins.MappingDisplayAsBus = m_displayAsBusCheckBox.Checked;
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
