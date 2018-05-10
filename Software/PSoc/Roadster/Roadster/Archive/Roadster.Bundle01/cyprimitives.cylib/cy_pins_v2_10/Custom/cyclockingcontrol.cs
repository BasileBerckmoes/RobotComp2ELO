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

namespace Cypress.Comps.PinsAndPorts.cy_pins_v2_10
{
    public partial class CyClockingControl : UserControl, ICyParamEditingControl
    {
        public static readonly CyPinData.ErrorMgrKey[] OwnedSettings = new CyPinData.ErrorMgrKey[]
        {
            CyPinData.ErrorMgrKey.CLOCK_INPUT,
            CyPinData.ErrorMgrKey.CLOCK_INPUT_ENABLE,
            CyPinData.ErrorMgrKey.CLOCK_INPUT_ENABLE_ON,
            CyPinData.ErrorMgrKey.CLOCK_INPUT_RESET,
            CyPinData.ErrorMgrKey.CLOCK_OUTPUT,
            CyPinData.ErrorMgrKey.CLOCK_OUTPUT_ENABLE,
            CyPinData.ErrorMgrKey.CLOCK_OUTPUT_ENABLE_ON,
            CyPinData.ErrorMgrKey.CLOCK_OUTPUT_RESET,
            CyPinData.ErrorMgrKey.CLOCK_OUTPUT_RESET_ENABLE,
            CyPinData.ErrorMgrKey.CLOCK_OE_RESET_ENABLE,
        };

        private const int BUS_CLK_IDX = -1;
        private const int EXTERNAL_IDX = -2;
        private const int NONE_IDX = -3;

        const string NAME_NONE = "None";
        readonly string NAME_BUS_CLK;
        const string NAME_EXTERNAL = "External";
        const string NAME_INVERTED = " (inverted)";

        private readonly CyPinData m_pins;
        private readonly CyErrorManager m_errMgr;

        public CyClockingControl(CyDeviceSupport deviceSupport, CyErrorManager errMgr, CyPinData pins)
        {
            InitializeComponent();

            m_pins = pins;
            m_errMgr = errMgr;
            Dock = DockStyle.Fill;

            NAME_BUS_CLK = (deviceSupport.IsPSoC4 || deviceSupport.IsTSG4) ? "HFCLK" : "BUS_CLK";

            m_inEnableModeComboBox.DropDownStyle = ComboBoxStyle.DropDownList;
            m_inClockComboBox.DropDownStyle = ComboBoxStyle.DropDownList;
            m_inClockEnComboBox.DropDownStyle = ComboBoxStyle.DropDownList;
            m_inResetComboBox.DropDownStyle = ComboBoxStyle.DropDownList;
            m_outEnableModeComboBox.DropDownStyle = ComboBoxStyle.DropDownList;
            m_outClockComboBox.DropDownStyle = ComboBoxStyle.DropDownList;
            m_outClockEnComboBox.DropDownStyle = ComboBoxStyle.DropDownList;
            m_outResetComboBox.DropDownStyle = ComboBoxStyle.DropDownList;

            UpdateData(); // Also enables events when it is done

            errMgr.RegisterSettingOwner(CyPinData.ErrorMgrKey.CLOCK_INPUT, m_errorProvider, m_inClockComboBox);
            errMgr.RegisterSettingOwner(CyPinData.ErrorMgrKey.CLOCK_INPUT_ENABLE, m_errorProvider, m_inClockEnComboBox);
            errMgr.RegisterSettingOwner(CyPinData.ErrorMgrKey.CLOCK_INPUT_ENABLE_ON, m_errorProvider, m_inEnableModeComboBox);
            errMgr.RegisterSettingOwner(CyPinData.ErrorMgrKey.CLOCK_INPUT_RESET, m_errorProvider, m_inResetComboBox);
            errMgr.RegisterSettingOwner(CyPinData.ErrorMgrKey.CLOCK_OUTPUT, m_errorProvider, m_outClockComboBox);
            errMgr.RegisterSettingOwner(CyPinData.ErrorMgrKey.CLOCK_OUTPUT_ENABLE, m_errorProvider, m_outClockEnComboBox);
            errMgr.RegisterSettingOwner(CyPinData.ErrorMgrKey.CLOCK_OUTPUT_ENABLE_ON, m_errorProvider, m_outEnableModeComboBox);
            errMgr.RegisterSettingOwner(CyPinData.ErrorMgrKey.CLOCK_OUTPUT_RESET, m_errorProvider, m_outResetComboBox);
            errMgr.RegisterSettingOwner(CyPinData.ErrorMgrKey.CLOCK_OUTPUT_RESET_ENABLE, m_errorProvider, m_outputResetCheckBox);
            errMgr.RegisterSettingOwner(CyPinData.ErrorMgrKey.CLOCK_OE_RESET_ENABLE, m_errorProvider, m_oeResetCheckBox);
        }

        private void EnableEvents()
        {
            m_pins.PinCountOrTypeChanged += m_pinsCountOrTypeChanged;
            m_inClockComboBox.SelectedIndexChanged += m_inClockComboBox_SelectedIndexChanged;
            m_inClockEnComboBox.SelectedIndexChanged += m_inClockEnComboBox_SelectedIndexChanged;
            m_inResetComboBox.SelectedIndexChanged += m_inResetComboBox_SelectedIndexChanged;
            m_inEnableModeComboBox.SelectedIndexChanged += m_inEnableModeComboBox_SelectedIndexChanged;
            m_outputResetCheckBox.CheckedChanged += m_outputResetCheckBox_CheckedChanged;
            m_oeResetCheckBox.CheckedChanged += m_oeResetCheckBox_CheckedChanged;
            m_outClockComboBox.SelectedIndexChanged += m_outClockComboBox_SelectedIndexChanged;
            m_outClockEnComboBox.SelectedIndexChanged += m_outClockEnComboBox_SelectedIndexChanged;
            m_outResetComboBox.SelectedIndexChanged += m_outResetComboBox_SelectedIndexChanged;
            m_outEnableModeComboBox.SelectedIndexChanged += m_outEnableModeComboBox_SelectedIndexChanged;
        }

        private void DisableEvents()
        {
            m_pins.PinCountOrTypeChanged -= m_pinsCountOrTypeChanged;
            m_inClockComboBox.SelectedIndexChanged -= m_inClockComboBox_SelectedIndexChanged;
            m_inClockEnComboBox.SelectedIndexChanged -= m_inClockEnComboBox_SelectedIndexChanged;
            m_inResetComboBox.SelectedIndexChanged -= m_inResetComboBox_SelectedIndexChanged;
            m_inEnableModeComboBox.SelectedIndexChanged -= m_inEnableModeComboBox_SelectedIndexChanged;
            m_outputResetCheckBox.CheckedChanged -= m_outputResetCheckBox_CheckedChanged;
            m_oeResetCheckBox.CheckedChanged -= m_oeResetCheckBox_CheckedChanged;
            m_outClockComboBox.SelectedIndexChanged -= m_outClockComboBox_SelectedIndexChanged;
            m_outClockEnComboBox.SelectedIndexChanged -= m_outClockEnComboBox_SelectedIndexChanged;
            m_outResetComboBox.SelectedIndexChanged -= m_outResetComboBox_SelectedIndexChanged;
            m_outEnableModeComboBox.SelectedIndexChanged -= m_outEnableModeComboBox_SelectedIndexChanged;
        }

        internal void UpdateData()
        {
            DisableEvents();
            PopulateDropDowns();

            m_inClockComboBox.SelectedIndex = GetIndex(m_inClockComboBox, m_pins.ClockInput);
            m_inClockEnComboBox.SelectedIndex = GetIndex(m_inClockEnComboBox, m_pins.ClockInputEnable);
            m_inEnableModeComboBox.SelectedIndex = Utils.GetIndex<CyPinClockEnable>(m_inEnableModeComboBox, m_pins.ClockInputEnableOn);
            m_inResetComboBox.SelectedIndex = GetIndex(m_inResetComboBox, m_pins.ClockInputReset);
            m_outClockComboBox.SelectedIndex = GetIndex(m_outClockComboBox, m_pins.ClockOutput);
            m_outClockEnComboBox.SelectedIndex = GetIndex(m_outClockEnComboBox, m_pins.ClockOutputEnable);
            m_outEnableModeComboBox.SelectedIndex = Utils.GetIndex<CyPinClockEnable>(m_outEnableModeComboBox, m_pins.ClockOutputEnableOn);
            m_outResetComboBox.SelectedIndex = GetIndex(m_outResetComboBox, m_pins.ClockOutputReset);
            m_outputResetCheckBox.Checked = m_pins.ClockOutputResetEnable;
            m_oeResetCheckBox.Checked = m_pins.ClockOutputOeResetEnable;

            m_inEnableModeComboBox.Enabled = (m_pins.ClockInputEnable != CyPinClockEnRst.NONE);
            m_outEnableModeComboBox.Enabled = (m_pins.ClockOutputEnable != CyPinClockEnRst.NONE);
            EnableEvents();
        }

        private void PopulateDropDowns()
        {
            const int IN_CLK_BASE_ITEMS = 4;

            if (0 == m_inClockComboBox.Items.Count)
            {
                m_inClockComboBox.Items.Add(new CyPaSelect(BUS_CLK_IDX, false, NAME_BUS_CLK));
                m_inClockComboBox.Items.Add(new CyPaSelect(BUS_CLK_IDX, true, NAME_BUS_CLK + NAME_INVERTED));
                m_inClockComboBox.Items.Add(new CyPaSelect(EXTERNAL_IDX, false, NAME_EXTERNAL));
                m_inClockComboBox.Items.Add(new CyPaSelect(EXTERNAL_IDX, true, NAME_EXTERNAL + NAME_INVERTED));

                m_inClockEnComboBox.Items.Add(new CyPaSelect(NONE_IDX, false, NAME_NONE));
                m_inClockEnComboBox.Items.Add(new CyPaSelect(EXTERNAL_IDX, false, NAME_EXTERNAL));
                m_inClockEnComboBox.Items.Add(new CyPaSelect(EXTERNAL_IDX, true, NAME_EXTERNAL + NAME_INVERTED));

                m_inEnableModeComboBox.Items.Add(
                    new CyComboItem<CyPinClockEnable>(CyPinClockEnable.RISING_EDGE, "Rising edge"));
                m_inEnableModeComboBox.Items.Add(new CyComboItem<CyPinClockEnable>(CyPinClockEnable.LEVEL, "Level"));

                m_inResetComboBox.Items.Add(new CyPaSelect(NONE_IDX, false, NAME_NONE));
                m_inResetComboBox.Items.Add(new CyPaSelect(EXTERNAL_IDX, false, NAME_EXTERNAL));
                m_inResetComboBox.Items.Add(new CyPaSelect(EXTERNAL_IDX, true, NAME_EXTERNAL + NAME_INVERTED));

                m_outClockComboBox.Items.Add(new CyPaSelect(BUS_CLK_IDX, false, NAME_BUS_CLK));
                m_outClockComboBox.Items.Add(new CyPaSelect(BUS_CLK_IDX, true, NAME_BUS_CLK + NAME_INVERTED));
                m_outClockComboBox.Items.Add(new CyPaSelect(EXTERNAL_IDX, false, NAME_EXTERNAL));
                m_outClockComboBox.Items.Add(new CyPaSelect(EXTERNAL_IDX, true, NAME_EXTERNAL + NAME_INVERTED));

                m_outClockEnComboBox.Items.Add(new CyPaSelect(NONE_IDX, false, NAME_NONE));
                m_outClockEnComboBox.Items.Add(new CyPaSelect(EXTERNAL_IDX, false, NAME_EXTERNAL));
                m_outClockEnComboBox.Items.Add(new CyPaSelect(EXTERNAL_IDX, true, NAME_EXTERNAL + NAME_INVERTED));

                m_outEnableModeComboBox.Items.Add(
                    new CyComboItem<CyPinClockEnable>(CyPinClockEnable.RISING_EDGE, "Rising Edge"));
                m_outEnableModeComboBox.Items.Add(new CyComboItem<CyPinClockEnable>(CyPinClockEnable.LEVEL, "Level"));

                m_outResetComboBox.Items.Add(new CyPaSelect(NONE_IDX, false, NAME_NONE));
                m_outResetComboBox.Items.Add(new CyPaSelect(EXTERNAL_IDX, false, NAME_EXTERNAL));
                m_outResetComboBox.Items.Add(new CyPaSelect(EXTERNAL_IDX, true, NAME_EXTERNAL + NAME_INVERTED));
            }

            while (m_inClockComboBox.Items.Count > IN_CLK_BASE_ITEMS)
            {
                m_inClockComboBox.Items.RemoveAt(IN_CLK_BASE_ITEMS);
                m_inClockEnComboBox.Items.RemoveAt(IN_CLK_BASE_ITEMS - 1);
                m_inResetComboBox.Items.RemoveAt(IN_CLK_BASE_ITEMS - 1);
                m_outClockComboBox.Items.RemoveAt(IN_CLK_BASE_ITEMS);
                m_outClockEnComboBox.Items.RemoveAt(IN_CLK_BASE_ITEMS - 1);
                m_outResetComboBox.Items.RemoveAt(IN_CLK_BASE_ITEMS - 1);
            }

            for (byte i = 0; i < m_pins.PinCount; i++)
            {
                CyPinData.PerPin pin = m_pins[i];

                if ((pin.Type & (CyPinType.BIDIRECTIONAL | CyPinType.DIGITAL_IN)) > 0)
                {
                    string name = m_pins.GetPinPoundDefineName(i);
                    CyPaSelect reg = new CyPaSelect(i, false, name);
                    CyPaSelect inv = new CyPaSelect(i, true, name + NAME_INVERTED);

                    m_inClockComboBox.Items.Add(reg);
                    m_inClockComboBox.Items.Add(inv);
                    m_inClockEnComboBox.Items.Add(reg);
                    m_inClockEnComboBox.Items.Add(inv);
                    m_inResetComboBox.Items.Add(reg);
                    m_inResetComboBox.Items.Add(inv);
                    m_outClockComboBox.Items.Add(reg);
                    m_outClockComboBox.Items.Add(inv);
                    m_outClockEnComboBox.Items.Add(reg);
                    m_outClockEnComboBox.Items.Add(inv);
                    m_outResetComboBox.Items.Add(reg);
                    m_outResetComboBox.Items.Add(inv);
                }
            }
        }

        void m_pinsCountOrTypeChanged()
        {
            UpdateData();
        }

        void m_inClockComboBox_SelectedIndexChanged(object sender, EventArgs e)
        {
            CyPinClock clk = GetPinClock((CyPaSelect)m_inClockComboBox.SelectedItem);
            m_pins.ClockInput = clk;
            if(clk == CyPinClock.PIN || clk == CyPinClock.PIN_INV)
                UpdatePortAdapterPin(m_inClockComboBox, clk == CyPinClock.PIN_INV);
        }

        void m_inClockEnComboBox_SelectedIndexChanged(object sender, EventArgs e)
        {
            CyPinClockEnRst clk = GetPinClockEnableReset((CyPaSelect)m_inClockEnComboBox.SelectedItem);
            m_pins.ClockInputEnable = clk;
            if(clk == CyPinClockEnRst.PIN || clk == CyPinClockEnRst.PIN_INV)
                UpdatePortAdapterPin(m_inClockEnComboBox, clk == CyPinClockEnRst.PIN_INV);
            m_inEnableModeComboBox.Enabled = (CyPinClockEnRst.NONE != clk);
        }

        void m_inEnableModeComboBox_SelectedIndexChanged(object sender, EventArgs e)
        {
            m_pins.ClockInputEnableOn = ((CyComboItem<CyPinClockEnable>)m_inEnableModeComboBox.SelectedItem).Item;
        }

        void m_inResetComboBox_SelectedIndexChanged(object sender, EventArgs e)
        {
            CyPinClockEnRst clk = GetPinClockEnableReset((CyPaSelect)m_inResetComboBox.SelectedItem);
            m_pins.ClockInputReset = clk;
            if(clk == CyPinClockEnRst.PIN || clk == CyPinClockEnRst.PIN_INV)
                UpdatePortAdapterPin(m_inResetComboBox, clk == CyPinClockEnRst.PIN_INV);
        }

        void m_outClockComboBox_SelectedIndexChanged(object sender, EventArgs e)
        {
            CyPinClock clk = GetPinClock((CyPaSelect)m_outClockComboBox.SelectedItem);
            m_pins.ClockOutput = clk;
            if(clk == CyPinClock.PIN || clk == CyPinClock.PIN_INV)
                UpdatePortAdapterPin(m_outClockComboBox, clk == CyPinClock.PIN_INV);
        }

        void m_outClockEnComboBox_SelectedIndexChanged(object sender, EventArgs e)
        {
            CyPinClockEnRst clk = GetPinClockEnableReset((CyPaSelect)m_outClockEnComboBox.SelectedItem);
            m_pins.ClockOutputEnable = clk;
            if(clk == CyPinClockEnRst.PIN || clk == CyPinClockEnRst.PIN_INV)
                UpdatePortAdapterPin(m_outClockEnComboBox, clk == CyPinClockEnRst.PIN_INV);
            m_outEnableModeComboBox.Enabled = (CyPinClockEnRst.NONE != clk);
        }

        void m_outEnableModeComboBox_SelectedIndexChanged(object sender, EventArgs e)
        {
            m_pins.ClockOutputEnableOn = ((CyComboItem<CyPinClockEnable>)m_outEnableModeComboBox.SelectedItem).Item;
        }

        void m_outputResetCheckBox_CheckedChanged(object sender, EventArgs e)
        {
            m_pins.ClockOutputResetEnable = m_outputResetCheckBox.Checked;
        }

        void m_oeResetCheckBox_CheckedChanged(object sender, EventArgs e)
        {
            m_pins.ClockOutputOeResetEnable = m_oeResetCheckBox.Checked;
        }

        void m_outResetComboBox_SelectedIndexChanged(object sender, EventArgs e)
        {
            CyPinClockEnRst clk = GetPinClockEnableReset((CyPaSelect)m_outResetComboBox.SelectedItem);
            m_pins.ClockOutputReset = clk;
            if(clk == CyPinClockEnRst.PIN || clk == CyPinClockEnRst.PIN_INV)
                UpdatePortAdapterPin(m_outResetComboBox, clk == CyPinClockEnRst.PIN_INV);
        }

        private void UpdatePortAdapterPin(ComboBox cbo, bool isInverse)
        {
            if (isInverse)
                UpdatePortAdapterPin((CyPaSelect)cbo.Items[cbo.SelectedIndex - 1], (CyPaSelect)cbo.SelectedItem);
            else
                UpdatePortAdapterPin((CyPaSelect)cbo.SelectedItem, (CyPaSelect)cbo.Items[cbo.SelectedIndex + 1]);
        }

        private void UpdatePortAdapterPin(CyPaSelect opt, CyPaSelect optInv)
        {
            Debug.Assert(opt.ClockSelectIdx == optInv.ClockSelectIdx);
            Debug.Assert(!opt.Invert && opt.Invert);
            if (opt.ClockSelectIdx >= 0 && m_pins.ClockPAPin != opt.ClockSelectIdx)
            {
                CyPaSelect item;
                m_pins.ClockPAPin = opt.ClockSelectIdx;

                // go set the PA Pin for any of the 6 that were using the PA pin
                item = (CyPaSelect)m_inClockComboBox.SelectedItem;
                if (item.ClockSelectIdx >= 0)
                    m_inClockComboBox.SelectedItem = item.Invert ? optInv : opt;

                item = (CyPaSelect)m_inClockEnComboBox.SelectedItem;
                if (item.ClockSelectIdx >= 0)
                    m_inClockEnComboBox.SelectedItem = item.Invert ? optInv : opt;

                item = (CyPaSelect)m_inResetComboBox.SelectedItem;
                if (item.ClockSelectIdx >= 0)
                    m_inResetComboBox.SelectedItem = item.Invert ? optInv : opt;

                item = (CyPaSelect)m_outClockComboBox.SelectedItem;
                if (item.ClockSelectIdx >= 0)
                    m_outClockComboBox.SelectedItem = item.Invert ? optInv : opt;

                item = (CyPaSelect)m_outClockEnComboBox.SelectedItem;
                if (item.ClockSelectIdx >= 0)
                    m_outClockEnComboBox.SelectedItem = item.Invert ? optInv : opt;

                item = (CyPaSelect)m_outResetComboBox.SelectedItem;
                if (item.ClockSelectIdx >= 0)
                    m_outResetComboBox.SelectedItem = item.Invert ? optInv : opt;
            }
        }

        private static CyPinClock GetPinClock(CyPaSelect selectedItem)
        {
            switch (selectedItem.ClockSelectIdx)
            {
                case BUS_CLK_IDX:
                    return selectedItem.Invert ? CyPinClock.HFCLK_INV : CyPinClock.HFCLK;
                case EXTERNAL_IDX:
                    return selectedItem.Invert ? CyPinClock.EXTERNAL_INV : CyPinClock.EXTERNAL;
                default:
                    Debug.Assert(selectedItem.ClockSelectIdx >= 0);
                    return selectedItem.Invert ? CyPinClock.PIN_INV : CyPinClock.PIN;
            }
        }
        private static CyPinClockEnRst GetPinClockEnableReset(CyPaSelect selectedItem)
        {
            switch (selectedItem.ClockSelectIdx)
            {
                case NONE_IDX:
                    return CyPinClockEnRst.NONE;
                case EXTERNAL_IDX:
                    return selectedItem.Invert ? CyPinClockEnRst.EXTERNAL_INV : CyPinClockEnRst.EXTERNAL;
                default:
                    Debug.Assert(selectedItem.ClockSelectIdx >= 0);
                    return selectedItem.Invert ? CyPinClockEnRst.PIN_INV : CyPinClockEnRst.PIN;
            }
        }

        private static int GetIndex(ComboBox cbo, CyPinClock clk)
        {
            for (int i = 0; i < cbo.Items.Count; i++)
            {
                if (clk == GetPinClock((CyPaSelect)cbo.Items[i]))
                    return i;
            }
            return -1;
        }

        private static int GetIndex(ComboBox cbo, CyPinClockEnRst clk)
        {
            for (int i = 0; i < cbo.Items.Count; i++)
            {
                if (clk == GetPinClockEnableReset((CyPaSelect)cbo.Items[i]))
                    return i;
            }
            return -1;
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

        class CyPaSelect
        {
            public readonly bool Invert;
            public readonly int ClockSelectIdx;
            public readonly string Name;

            public CyPaSelect(int clockSelectIdx, bool invert, string name)
            {
                ClockSelectIdx = clockSelectIdx;
                Invert = invert;
                Name = name;
            }

            public override string ToString()
            {
                return Name;
            }
        }
    }
}
