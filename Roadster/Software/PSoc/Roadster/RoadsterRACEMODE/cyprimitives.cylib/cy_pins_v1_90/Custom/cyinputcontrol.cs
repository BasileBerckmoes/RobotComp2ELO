/*******************************************************************************
* Copyright 2008-2009, Cypress Semiconductor Corporation.  All rights reserved.
* You may use this file only in accordance with the license, terms, conditions, 
* disclaimers, and limitations in the end user license agreement accompanying 
* the software package with which this file was provided.
********************************************************************************/

using System;
using System.Windows.Forms;
using System.Diagnostics;
using CyDesigner.Extensions.Gde;
using Cypress.Comps.PinsAndPorts.Common_v1_90;

namespace Cypress.Comps.PinsAndPorts.cy_pins_v1_90
{
    public partial class CyInputControl : UserControl
    {
        CyPerPinDataControl m_perPinDataControl;
        ICyInstEdit_v1 m_instEdit;

        public CyPerPinDataControl PerPinDataControl
        {
            get { return m_perPinDataControl; }
            set { m_perPinDataControl = value; }
        }

        public CyInputControl(ICyInstEdit_v1 instEdit)
        {
            m_instEdit = instEdit;
            InitializeComponent();

            m_inputBufferEnabledCheckBox.Enabled = !instEdit.DeviceQuery.IsTSG4;

            m_thresholdComboBox.DropDownStyle = ComboBoxStyle.DropDownList;
            m_thresholdComboBox.Items.Add(new CyThresholdLevel(CyThresholdLevel.CyThreshold.CMOS));
            m_thresholdComboBox.Items.Add(new CyThresholdLevel(CyThresholdLevel.CyThreshold.CMOS_LVTTL));
            m_thresholdComboBox.Items.Add(new CyThresholdLevel(CyThresholdLevel.CyThreshold.LVTTL));
            m_thresholdComboBox.Items.Add(new CyThresholdLevel(CyThresholdLevel.CyThreshold.PT4_VDDIO));
            m_thresholdComboBox.Items.Add(new CyThresholdLevel(CyThresholdLevel.CyThreshold.PT5_VDDIO));
            m_thresholdComboBox.Items.Add(new CyThresholdLevel(CyThresholdLevel.CyThreshold.PT5_VREF));
            m_thresholdComboBox.Items.Add(new CyThresholdLevel(CyThresholdLevel.CyThreshold.VREF));

            m_interruptComboBox.DropDownStyle = ComboBoxStyle.DropDownList;
            m_interruptComboBox.Items.Add(new CyInterruptMode(CyInterruptMode.CyInterrupt.None));
            m_interruptComboBox.Items.Add(new CyInterruptMode(CyInterruptMode.CyInterrupt.Rising));
            m_interruptComboBox.Items.Add(new CyInterruptMode(CyInterruptMode.CyInterrupt.Falling));
            m_interruptComboBox.Items.Add(new CyInterruptMode(CyInterruptMode.CyInterrupt.Both));

            m_inputSyncComboBox.DropDownStyle = ComboBoxStyle.DropDownList;
            m_inputSyncComboBox.Items.Add(new CyInputSyncMode(CyInputSyncMode.CyInputSync.DoubleSync));
            if (instEdit.DeviceQuery.IsPSoC4)
            {
                m_inputSyncComboBox.Items.Add(new CyInputSyncMode(CyInputSyncMode.CyInputSync.SingleSync));
            }
            m_inputSyncComboBox.Items.Add(new CyInputSyncMode(CyInputSyncMode.CyInputSync.Transparent));

            m_hotSwapCheckBox.CheckedChanged += m_hotSwapCheckBox_CheckedChanged;
            m_inputBufferEnabledCheckBox.CheckedChanged += m_inputBufferEnabledCheckBox_CheckedChanged;
            m_inputSyncComboBox.SelectedIndexChanged += m_inputSyncComboBox_SelectedIndexChanged;
            m_interruptComboBox.SelectedIndexChanged += m_interruptComboBox_SelectedIndexChanged;
            m_thresholdComboBox.SelectedIndexChanged += m_thresholdComboBox_SelectedIndexChanged;
            m_hysteresisCheckBox.CheckedChanged += m_hysteresisCheckBox_CheckedChanged;
            
            m_errorProvider.SetIconAlignment(m_hotSwapCheckBox, ErrorIconAlignment.MiddleLeft);
            m_errorProvider.SetIconPadding(m_hotSwapCheckBox, 3);
            m_errorProvider.SetIconAlignment(m_inputBufferEnabledCheckBox, ErrorIconAlignment.MiddleLeft);
            m_errorProvider.SetIconPadding(m_inputBufferEnabledCheckBox, 3);
            m_errorProvider.SetIconAlignment(m_inputSyncComboBox, ErrorIconAlignment.MiddleLeft);
            m_errorProvider.SetIconPadding(m_inputSyncComboBox, 3);
            m_errorProvider.SetIconAlignment(m_interruptComboBox, ErrorIconAlignment.MiddleLeft);
            m_errorProvider.SetIconPadding(m_interruptComboBox, 3);
            m_errorProvider.SetIconAlignment(m_thresholdComboBox, ErrorIconAlignment.MiddleLeft);
            m_errorProvider.SetIconPadding(m_thresholdComboBox, 3);
        }

        void m_thresholdComboBox_SelectedIndexChanged(object sender, EventArgs e)
        {
            PerPinDataControl.OnParamDataChangeByUser(new CyPerPinDataEventArgs(
                CyParamInfo.Formal_ParamName_ThresholdLevels, InputThresholdLevel));
            UpdateHysteresisEnabled();
        }

        void m_interruptComboBox_SelectedIndexChanged(object sender, EventArgs e)
        {
            PerPinDataControl.OnParamDataChangeByUser(new CyPerPinDataEventArgs(
                CyParamInfo.Formal_ParamName_InterruptMode, InterruptMode));
        }

        void m_inputSyncComboBox_SelectedIndexChanged (object sender, EventArgs e)
        {
            string inputSynchronized = InputSyncModeCombo == CyPortConstants.InputSyncModeValue_TRANSPARENT
                                           ? CyPortConstants.InputsSynchronizedValue_DISABLED
                                           : CyPortConstants.InputsSynchronizedValue_ENABLED;
            string inputSyncMode = InputSyncModeCombo == CyPortConstants.InputSyncModeValue_SINGLESYNC
                                       ? CyPortConstants.InputsSyncModeValue_SINGLE
                                       : CyPortConstants.InputsSyncModeValue_DOUBLE;
            PerPinDataControl.OnParamDataChangeByUser(new CyPerPinDataEventArgs(
                CyParamInfo.Formal_ParamName_InputsSynchronized, inputSynchronized));
            PerPinDataControl.OnParamDataChangeByUser(new CyPerPinDataEventArgs(
                CyParamInfo.Formal_ParamName_InputsSyncMode, inputSyncMode));
        }

        void m_inputBufferEnabledCheckBox_CheckedChanged(object sender, EventArgs e)
        {
            PerPinDataControl.OnParamDataChangeByUser(new CyPerPinDataEventArgs(
                CyParamInfo.Formal_ParamName_InputBuffersEnabled, InputBufferEnabled));
        }

        void m_hysteresisCheckBox_CheckedChanged(object sender, EventArgs e)
        {
            PerPinDataControl.OnParamDataChangeByUser(new CyPerPinDataEventArgs(
                CyParamInfo.Formal_ParamName_ThresholdLevels, InputThresholdLevel));
        }

        void m_hotSwapCheckBox_CheckedChanged(object sender, EventArgs e)
        {
            PerPinDataControl.OnParamDataChangeByUser(new CyPerPinDataEventArgs(
                CyParamInfo.Formal_ParamName_HotSwaps, HotSwap));
        }

        public string HotSwap
        {
            get
            {
                if (m_hotSwapCheckBox.CheckState == CheckState.Indeterminate)
                {
                    return null;
                }
                return m_hotSwapCheckBox.Checked
                           ? CyPortConstants.HotSwapValue_TRUE
                           : CyPortConstants.HotSwapValue_FALSE;
            }

            set
            {
                m_hotSwapCheckBox.CheckedChanged -= m_hotSwapCheckBox_CheckedChanged;
                if (value == null)
                {
                    m_hotSwapCheckBox.CheckState = CheckState.Indeterminate;
                }
                else
                {
                    switch (value)
                    {
                        case CyPortConstants.HotSwapValue_FALSE:
                            m_hotSwapCheckBox.CheckState = CheckState.Unchecked;
                            m_hotSwapCheckBox.Checked = false;
                            break;

                        case CyPortConstants.HotSwapValue_TRUE:
                            m_hotSwapCheckBox.CheckState = CheckState.Checked;
                            m_hotSwapCheckBox.Checked = true;
                            break;

                        default:
                            m_hotSwapCheckBox.CheckState = CheckState.Indeterminate;
                            break;
                    }
                }
                m_hotSwapCheckBox.CheckedChanged += m_hotSwapCheckBox_CheckedChanged;
            }
        }

        public string InputBufferEnabled
        {
            get
            {
                if (m_inputBufferEnabledCheckBox.CheckState == CheckState.Indeterminate)
                {
                    return null;
                }
                return m_inputBufferEnabledCheckBox.Checked
                           ? CyPortConstants.InputBufferEnabledValue_TRUE
                           : CyPortConstants.InputBufferEnabledValue_FALSE;
            }

            set
            {
                m_inputBufferEnabledCheckBox.CheckedChanged -= m_inputBufferEnabledCheckBox_CheckedChanged;
                if (value == null)
                {
                    m_inputBufferEnabledCheckBox.CheckState = CheckState.Indeterminate;
                }
                else
                {
                    switch (value)
                    {
                        case CyPortConstants.InputBufferEnabledValue_FALSE:
                            m_inputBufferEnabledCheckBox.CheckState = CheckState.Unchecked;
                            m_inputBufferEnabledCheckBox.Checked = false;
                            break;

                        case CyPortConstants.InputBufferEnabledValue_TRUE:
                            m_inputBufferEnabledCheckBox.CheckState = CheckState.Checked;
                            m_inputBufferEnabledCheckBox.Checked = true;
                            break;

                        default:
                            m_inputBufferEnabledCheckBox.CheckState = CheckState.Indeterminate;
                            break;
                    }
                }
                m_inputBufferEnabledCheckBox.Enabled = !m_instEdit.DeviceQuery.IsTSG4;

                m_inputBufferEnabledCheckBox.CheckedChanged += m_inputBufferEnabledCheckBox_CheckedChanged;
            }
        }

        public string InputSyncModeCombo
        {
            get
            {
                CyInputSyncMode syncMode = m_inputSyncComboBox.SelectedItem as CyInputSyncMode;
                if (syncMode == null)
                {
                    return null;
                }
                if (syncMode.InputSync == CyInputSyncMode.CyInputSync.SingleSync)
                    return CyPortConstants.InputSyncModeValue_SINGLESYNC;
                if (syncMode.InputSync == CyInputSyncMode.CyInputSync.DoubleSync)
                    return CyPortConstants.InputsSyncModeValue_DOUBLE;
                if (syncMode.InputSync == CyInputSyncMode.CyInputSync.Transparent)
                    return CyPortConstants.InputSyncModeValue_TRANSPARENT;
                return null;
            }

            set
            {
                m_inputSyncComboBox.SelectedIndexChanged -= m_inputSyncComboBox_SelectedIndexChanged;
                if (value == null)
                {
                    m_inputSyncComboBox.SelectedItem = null;
                }
                else
                {
                    switch (value)
                    {
                        case CyPortConstants.InputSyncModeValue_DOUBLESYNC:
                            Select(CyInputSyncMode.CyInputSync.DoubleSync);
                            break;

                        case CyPortConstants.InputSyncModeValue_SINGLESYNC:
                            Select(CyInputSyncMode.CyInputSync.SingleSync);
                            break;

                        case CyPortConstants.InputSyncModeValue_TRANSPARENT:
                            Select(CyInputSyncMode.CyInputSync.Transparent);
                            break;

                        default:
                            m_inputSyncComboBox.SelectedItem = null;
                            break;
                    }
                }
                m_inputSyncComboBox.SelectedIndexChanged += m_inputSyncComboBox_SelectedIndexChanged;
            }
        }

        public string InputThresholdLevel
        {
            get
            {
                CyThresholdLevel threshold = m_thresholdComboBox.SelectedItem as CyThresholdLevel;
                if (threshold == null || m_hysteresisCheckBox.CheckState == CheckState.Indeterminate)
                {
                    return null;
                }
                return threshold.GetParamValue(m_hysteresisCheckBox.Checked);
            }

            set
            {
                m_thresholdComboBox.SelectedIndexChanged -= m_thresholdComboBox_SelectedIndexChanged;
                m_hysteresisCheckBox.CheckedChanged -= m_hysteresisCheckBox_CheckedChanged;
                if (value == null)
                {
                    m_thresholdComboBox.SelectedItem = null;
                    m_hysteresisCheckBox.CheckState = CheckState.Indeterminate;
                }
                else
                {
                    switch (value)
                    {
                        case CyPortConstants.ThresholdLevelValue_CMOS:
                            Select(CyThresholdLevel.CyThreshold.CMOS);
                            m_hysteresisCheckBox.CheckState = CheckState.Unchecked;
                            m_hysteresisCheckBox.Checked = false;
                            break;

                        case CyPortConstants.ThresholdLevelValue_CMOS_LVTTL:
                            Select(CyThresholdLevel.CyThreshold.CMOS_LVTTL);
                            m_hysteresisCheckBox.CheckState = CheckState.Unchecked;
                            m_hysteresisCheckBox.Checked = false;
                            break;

                        case CyPortConstants.ThresholdLevelValue_LVTTL:
                            Select(CyThresholdLevel.CyThreshold.LVTTL);
                            m_hysteresisCheckBox.CheckState = CheckState.Unchecked;
                            m_hysteresisCheckBox.Checked = false;
                            break;

                        case CyPortConstants.ThresholdLevelValue_PT4_VDDIO:
                            Select(CyThresholdLevel.CyThreshold.PT4_VDDIO);
                            m_hysteresisCheckBox.CheckState = CheckState.Unchecked;
                            m_hysteresisCheckBox.Checked = false;
                            break;

                        case CyPortConstants.ThresholdLevelValue_PT4_VDDIO_HYST:
                            Select(CyThresholdLevel.CyThreshold.PT4_VDDIO);
                            m_hysteresisCheckBox.CheckState = CheckState.Checked;
                            m_hysteresisCheckBox.Checked = true;
                            break;

                        case CyPortConstants.ThresholdLevelValue_PT5_VDDIO:
                            Select(CyThresholdLevel.CyThreshold.PT5_VDDIO);
                            m_hysteresisCheckBox.CheckState = CheckState.Unchecked;
                            m_hysteresisCheckBox.Checked = false;
                            break;

                        case CyPortConstants.ThresholdLevelValue_PT5_VDDIO_HYST:
                            Select(CyThresholdLevel.CyThreshold.PT5_VDDIO);
                            m_hysteresisCheckBox.CheckState = CheckState.Checked;
                            m_hysteresisCheckBox.Checked = true;
                            break;

                        case CyPortConstants.ThresholdLevelValue_PT5_VREF:
                            Select(CyThresholdLevel.CyThreshold.PT5_VREF);
                            m_hysteresisCheckBox.CheckState = CheckState.Unchecked;
                            m_hysteresisCheckBox.Checked = false;
                            break;

                        case CyPortConstants.ThresholdLevelValue_PT5_VREF_HYST:
                            Select(CyThresholdLevel.CyThreshold.PT5_VREF);
                            m_hysteresisCheckBox.CheckState = CheckState.Checked;
                            m_hysteresisCheckBox.Checked = true;
                            break;

                        case CyPortConstants.ThresholdLevelValue_VREF:
                            Select(CyThresholdLevel.CyThreshold.VREF);
                            m_hysteresisCheckBox.CheckState = CheckState.Unchecked;
                            m_hysteresisCheckBox.Checked = false;
                            break;

                        case CyPortConstants.ThresholdLevelValue_VREF_HYST:
                            Select(CyThresholdLevel.CyThreshold.VREF);
                            m_hysteresisCheckBox.CheckState = CheckState.Checked;
                            m_hysteresisCheckBox.Checked = true;
                            break;

                        default:
                            Debug.Fail("unhandled");
                            m_thresholdComboBox.SelectedItem = null;
                            m_hysteresisCheckBox.CheckState = CheckState.Indeterminate;
                            break;
                    }
                }
                UpdateHysteresisEnabled();
                m_thresholdComboBox.SelectedIndexChanged += m_thresholdComboBox_SelectedIndexChanged;
                m_hysteresisCheckBox.CheckedChanged += m_hysteresisCheckBox_CheckedChanged;
            }
        }

        public string InterruptMode
        {
            get
            {
                CyInterruptMode intr = m_interruptComboBox.SelectedItem as CyInterruptMode;
                return intr == null ? null : intr.ParamValue;
            }

            set
            {
                m_interruptComboBox.SelectedIndexChanged -= m_interruptComboBox_SelectedIndexChanged;
                if (value == null)
                {
                    m_interruptComboBox.SelectedItem = null;
                }
                else
                {
                    switch (value)
                    {
                        case CyPortConstants.InterruptModeValue_FALLING_EDGE:
                            Select(CyInterruptMode.CyInterrupt.Falling);
                            break;

                        case CyPortConstants.InterruptModeValue_NONE:
                            Select(CyInterruptMode.CyInterrupt.None);
                            break;

                        case CyPortConstants.InterruptModeValue_ON_CHANGE:
                            Select(CyInterruptMode.CyInterrupt.Both);
                            break;

                        case CyPortConstants.InterruptModeValue_RISING_EDGE:
                            Select(CyInterruptMode.CyInterrupt.Rising);
                            break;

                        default:
                            Debug.Fail("unhandled");
                            m_interruptComboBox.SelectedItem = null;
                            break;
                    }
                }
                m_interruptComboBox.SelectedIndexChanged += m_interruptComboBox_SelectedIndexChanged;
            }
        }

        public string HotSwapErrorText
        {
            get { return m_errorProvider.GetError(m_hotSwapCheckBox); }
            set { m_errorProvider.SetError(m_hotSwapCheckBox, value); }
        }

        public string InputBufferEnabledErrorText
        {
            get { return m_errorProvider.GetError(m_inputBufferEnabledCheckBox); }
            set { m_errorProvider.SetError(m_inputBufferEnabledCheckBox, value); }
        }

        public string InputSynchronizedErrorText
        {
            get { return m_errorProvider.GetError(m_inputSyncComboBox); }
            set { m_errorProvider.SetError(m_inputSyncComboBox, value); }
        }

        public string InputSyncModeErrorText
        {
            get { return m_errorProvider.GetError(m_inputSyncComboBox); }
            set { m_errorProvider.SetError(m_inputSyncComboBox, value); }
        }

        public string InputThresholdLevelErrorText
        {
            get { return m_errorProvider.GetError(m_thresholdComboBox); }
            set { m_errorProvider.SetError(m_thresholdComboBox, value); }
        }

        public string InterruptModeErrorText
        {
            get { return m_errorProvider.GetError(m_interruptComboBox); }
            set { m_errorProvider.SetError(m_interruptComboBox, value); }
        }

        void Select(CyThresholdLevel.CyThreshold threshold)
        {
            foreach (CyThresholdLevel level in m_thresholdComboBox.Items)
            {
                if (level.Threshold == threshold)
                {
                    m_thresholdComboBox.SelectedItem = level;
                    break;
                }
            }
        }

        void Select(CyInterruptMode.CyInterrupt interrupt)
        {
            foreach (CyInterruptMode intr in m_interruptComboBox.Items)
            {
                if (intr.Interrupt == interrupt)
                {
                    m_interruptComboBox.SelectedItem = intr;
                    break;
                }
            }
        }

        void Select(CyInputSyncMode.CyInputSync inputSync)
        {
            foreach (CyInputSyncMode inp in m_inputSyncComboBox.Items)
            {
                if (inp.InputSync == inputSync)
                {
                    m_inputSyncComboBox.SelectedItem = inp;
                    break;
                }
            }
        }

        void UpdateHysteresisEnabled()
        {
            string threshold = InputThresholdLevel;
            if (threshold == null)
            {
                m_hysteresisCheckBox.Enabled = false;
            }
            else
            {
                switch (threshold)
                {
                    case CyPortConstants.ThresholdLevelValue_CMOS:
                    case CyPortConstants.ThresholdLevelValue_CMOS_LVTTL:
                    case CyPortConstants.ThresholdLevelValue_LVTTL:
                        m_hysteresisCheckBox.Enabled = false;
                        break;

                    case CyPortConstants.ThresholdLevelValue_PT4_VDDIO:
                    case CyPortConstants.ThresholdLevelValue_PT5_VDDIO:
                    case CyPortConstants.ThresholdLevelValue_PT5_VREF:
                    case CyPortConstants.ThresholdLevelValue_VREF:
                    case CyPortConstants.ThresholdLevelValue_PT4_VDDIO_HYST:
                    case CyPortConstants.ThresholdLevelValue_PT5_VDDIO_HYST:
                    case CyPortConstants.ThresholdLevelValue_PT5_VREF_HYST:
                    case CyPortConstants.ThresholdLevelValue_VREF_HYST:
                        m_hysteresisCheckBox.Enabled = true;
                        break;

                    default:
                        Debug.Fail("unhandled");
                        m_hysteresisCheckBox.Enabled = false;
                        break;
                }
            }
        }

        class CyThresholdLevel
        {
            public enum CyThreshold { CMOS, CMOS_LVTTL, LVTTL, PT4_VDDIO, PT5_VDDIO, PT5_VREF, VREF };

            public const String CyThresholdString_CMOS = "CMOS";
            public const String CyThresholdString_CMOSorLVTTL = "CMOS or LVTTL";
            public const String CyThresholdString_LVTTL = "LVTTL";
            public const String CyThresholdString_PT4_VDDIO = "0.4 x Vddio";
            public const String CyThresholdString_PT5_VDDIO = "0.5 x Vddio";
            public const String CyThresholdString_PT5_VREF = "0.5 x Vref";
            public const String CyThresholdString_VREF = "Vref";

            CyThreshold m_threshold;

            public CyThreshold Threshold { get { return m_threshold; } }

            public CyThresholdLevel(CyThreshold threshold)
            {
                m_threshold = threshold;
            }

            public string GetParamValue(bool hysteresis)
            {
                switch (Threshold)
                {
                    case CyThreshold.CMOS:
                        return CyPortConstants.ThresholdLevelValue_CMOS;

                    case CyThreshold.CMOS_LVTTL:
                        return CyPortConstants.ThresholdLevelValue_CMOS_LVTTL;

                    case CyThreshold.LVTTL:
                        return CyPortConstants.ThresholdLevelValue_LVTTL;

                    case CyThreshold.PT4_VDDIO:
                        return hysteresis
                                   ? CyPortConstants.ThresholdLevelValue_PT4_VDDIO_HYST
                                   : CyPortConstants.ThresholdLevelValue_PT4_VDDIO;

                    case CyThreshold.PT5_VDDIO:
                        return hysteresis
                                   ? CyPortConstants.ThresholdLevelValue_PT5_VDDIO_HYST
                                   : CyPortConstants.ThresholdLevelValue_PT5_VDDIO;

                    case CyThreshold.PT5_VREF:
                        return hysteresis
                                   ? CyPortConstants.ThresholdLevelValue_PT5_VREF_HYST
                                   : CyPortConstants.ThresholdLevelValue_PT5_VREF;

                    case CyThreshold.VREF:
                        return hysteresis
                                   ? CyPortConstants.ThresholdLevelValue_VREF_HYST
                                   : CyPortConstants.ThresholdLevelValue_VREF;

                    default:
                        Debug.Fail("unhandled");
                        return string.Empty;
                }
            }

            public override string ToString()
            {
                switch (Threshold)
                {
                    case CyThreshold.CMOS:
                        return CyThresholdString_CMOS;

                    case CyThreshold.CMOS_LVTTL:
                        return CyThresholdString_CMOSorLVTTL;

                    case CyThreshold.LVTTL:
                        return CyThresholdString_LVTTL;

                    case CyThreshold.PT4_VDDIO:
                        return CyThresholdString_PT4_VDDIO;

                    case CyThreshold.PT5_VDDIO:
                        return CyThresholdString_PT5_VDDIO;

                    case CyThreshold.PT5_VREF:
                        return CyThresholdString_PT5_VREF;

                    case CyThreshold.VREF:
                        return CyThresholdString_VREF;

                    default:
                        Debug.Fail("unhandled");
                        return base.ToString();
                }
            }
        }

        class CyInterruptMode
        {
            public enum CyInterrupt { None, Falling, Rising, Both };

            CyInterrupt m_interrupt;

            public CyInterrupt Interrupt { get { return m_interrupt; } }

            public CyInterruptMode(CyInterrupt interrupt)
            {
                m_interrupt = interrupt;
            }

            public string ParamValue
            {
                get
                {
                    switch (Interrupt)
                    {
                        case CyInterrupt.None:
                            return CyPortConstants.InterruptModeValue_NONE;

                        case CyInterrupt.Falling:
                            return CyPortConstants.InterruptModeValue_FALLING_EDGE;

                        case CyInterrupt.Rising:
                            return CyPortConstants.InterruptModeValue_RISING_EDGE;

                        case CyInterrupt.Both:
                            return CyPortConstants.InterruptModeValue_ON_CHANGE;

                        default:
                            Debug.Fail("unhandled");
                            return string.Empty;
                    }
                }
            }

            public override string ToString()
            {
                switch (Interrupt)
                {
                    case CyInterrupt.None:
                        return "None";

                    case CyInterrupt.Falling:
                        return "Falling Edge";

                    case CyInterrupt.Rising:
                        return "Rising Edge";

                    case CyInterrupt.Both:
                        return "Both Edges";

                    default:
                        Debug.Fail("unhandled");
                        return base.ToString();
                }
            }
        }

        class CyInputSyncMode
        {
            public enum CyInputSync { DoubleSync, SingleSync, Transparent };

            CyInputSync m_inputSync;

            public CyInputSync InputSync { get { return m_inputSync; } }

            public CyInputSyncMode(CyInputSync inputSync)
            {
                m_inputSync = inputSync;
            }

            public override string ToString()
            {
                switch (InputSync)
                {
                    case CyInputSync.DoubleSync:
                        return "Double-Sync";

                    case CyInputSync.SingleSync:
                        return "Single-Sync";

                    case CyInputSync.Transparent:
                        return "Transparent";

                    default:
                        Debug.Fail("unhandled");
                        return base.ToString();
                }
            }
        }
    }
}
