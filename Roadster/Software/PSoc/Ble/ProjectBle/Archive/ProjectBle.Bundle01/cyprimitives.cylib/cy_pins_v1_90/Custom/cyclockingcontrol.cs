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
using Cypress.Comps.PinsAndPorts.Common_v1_90;

namespace Cypress.Comps.PinsAndPorts.cy_pins_v1_90
{
    public partial class CyClockingControl : UserControl, ICyParamEditingControl
    {
        ICyInstEdit_v1 m_edit;
        private int m_paPin;

        public const int BUS_CLK_IDX = -1;
        public const int EXTERNAL_IDX = -2;
        public const int NONE_IDX = -3;

        public CyClockingControl(ICyInstEdit_v1 instEdit)
        {
            InitializeComponent();
            m_edit = instEdit;
            m_paPin = -1;

            this.Dock = DockStyle.Fill;

            m_inEnableModeComboBox.DropDownStyle = ComboBoxStyle.DropDownList;
            m_inClockComboBox.DropDownStyle = ComboBoxStyle.DropDownList;
            m_inClockEnComboBox.DropDownStyle = ComboBoxStyle.DropDownList;
            m_inResetComboBox.DropDownStyle = ComboBoxStyle.DropDownList;
            m_outEnableModeComboBox.DropDownStyle = ComboBoxStyle.DropDownList;
            m_outClockComboBox.DropDownStyle = ComboBoxStyle.DropDownList;
            m_outClockEnComboBox.DropDownStyle = ComboBoxStyle.DropDownList;
            m_outResetComboBox.DropDownStyle = ComboBoxStyle.DropDownList;

            PopulateDropDowns();

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

            bool inClkEnExternal, inClkEnPA;
            CyPortCustomizer.GetParamValue(m_edit, CyParamInfo.Formal_ParamName_ShowInClkEnTerm, out inClkEnExternal);
            CyPortCustomizer.GetParamValue(m_edit, CyParamInfo.Formal_ParamName_UsePaInClkEn, out inClkEnPA);
            m_inEnableModeComboBox.Enabled = inClkEnExternal || inClkEnPA;

            bool outClkEnExternal, outClkEnPA;
            CyPortCustomizer.GetParamValue(m_edit, CyParamInfo.Formal_ParamName_ShowOutClkEnTerm, out outClkEnExternal);
            CyPortCustomizer.GetParamValue(m_edit, CyParamInfo.Formal_ParamName_UsePaOutClkEn, out outClkEnPA);
            m_outEnableModeComboBox.Enabled = outClkEnExternal || outClkEnPA;
        }

        private void ClearDropDowns()
        {
            m_inEnableModeComboBox.Items.Clear();
            m_inClockComboBox.Items.Clear();
            m_inClockEnComboBox.Items.Clear();
            m_inResetComboBox.Items.Clear();
            m_outEnableModeComboBox.Items.Clear();
            m_outClockComboBox.Items.Clear();
            m_outClockEnComboBox.Items.Clear();
            m_outResetComboBox.Items.Clear();
        }

        private void PopulateDropDowns()
        {
            m_inEnableModeComboBox.Items.Add(new CyEnableType(CyEnableType.CyEnable.RisingEdge));
            m_inEnableModeComboBox.Items.Add(new CyEnableType(CyEnableType.CyEnable.Level));

            m_inClockComboBox.Items.Add(new CyPaSelect(BUS_CLK_IDX, false, m_edit));
            m_inClockComboBox.Items.Add(new CyPaSelect(BUS_CLK_IDX, true, m_edit));
            m_inClockComboBox.Items.Add(new CyPaSelect(EXTERNAL_IDX, false, m_edit));
            m_inClockComboBox.Items.Add(new CyPaSelect(EXTERNAL_IDX, true, m_edit));

            m_inClockEnComboBox.Items.Add(new CyPaSelect(NONE_IDX, false, m_edit));
            m_inClockEnComboBox.Items.Add(new CyPaSelect(EXTERNAL_IDX, false, m_edit));
            m_inClockEnComboBox.Items.Add(new CyPaSelect(EXTERNAL_IDX, true, m_edit));

            m_inResetComboBox.Items.Add(new CyPaSelect(NONE_IDX, false, m_edit));
            m_inResetComboBox.Items.Add(new CyPaSelect(EXTERNAL_IDX, false, m_edit));
            m_inResetComboBox.Items.Add(new CyPaSelect(EXTERNAL_IDX, true, m_edit));

            m_outEnableModeComboBox.Items.Add(new CyEnableType(CyEnableType.CyEnable.RisingEdge));
            m_outEnableModeComboBox.Items.Add(new CyEnableType(CyEnableType.CyEnable.Level));

            m_outClockComboBox.Items.Add(new CyPaSelect(BUS_CLK_IDX, false, m_edit));
            m_outClockComboBox.Items.Add(new CyPaSelect(BUS_CLK_IDX, true, m_edit));
            m_outClockComboBox.Items.Add(new CyPaSelect(EXTERNAL_IDX, false, m_edit));
            m_outClockComboBox.Items.Add(new CyPaSelect(EXTERNAL_IDX, true, m_edit));

            m_outClockEnComboBox.Items.Add(new CyPaSelect(NONE_IDX, false, m_edit));
            m_outClockEnComboBox.Items.Add(new CyPaSelect(EXTERNAL_IDX, false, m_edit));
            m_outClockEnComboBox.Items.Add(new CyPaSelect(EXTERNAL_IDX, true, m_edit));

            m_outResetComboBox.Items.Add(new CyPaSelect(NONE_IDX, false, m_edit));
            m_outResetComboBox.Items.Add(new CyPaSelect(EXTERNAL_IDX, false, m_edit));
            m_outResetComboBox.Items.Add(new CyPaSelect(EXTERNAL_IDX, true, m_edit));

            byte numPins;
            CyParamInfo.GetNumPinsValue(m_edit, out numPins);
            CyStringArrayParamData data;
            CyStringArrayParamData.CreateStringArrayData(m_edit, CyParamInfo.Formal_ParamName_PinTypes, out data);
            for (byte i = 0; i < numPins; i++)
            {
                string pinType = data.GetValue(i);
                if (CyPortConstants.IsInput(pinType) || CyPortConstants.IsBidir(pinType))
                {
                    m_inClockComboBox.Items.Add(new CyPaSelect(i, false, m_edit));
                    m_inClockComboBox.Items.Add(new CyPaSelect(i, true, m_edit));
                    m_inClockEnComboBox.Items.Add(new CyPaSelect(i, false, m_edit));
                    m_inClockEnComboBox.Items.Add(new CyPaSelect(i, true, m_edit));
                    m_inResetComboBox.Items.Add(new CyPaSelect(i, false, m_edit));
                    m_inResetComboBox.Items.Add(new CyPaSelect(i, true, m_edit));
                    m_outClockComboBox.Items.Add(new CyPaSelect(i, false, m_edit));
                    m_outClockComboBox.Items.Add(new CyPaSelect(i, true, m_edit));
                    m_outClockEnComboBox.Items.Add(new CyPaSelect(i, false, m_edit));
                    m_outClockEnComboBox.Items.Add(new CyPaSelect(i, true, m_edit));
                    m_outResetComboBox.Items.Add(new CyPaSelect(i, false, m_edit));
                    m_outResetComboBox.Items.Add(new CyPaSelect(i, true, m_edit));
                }
            }
        }

        int GetNumCanBePAPins()
        {
            byte numPins;
            int numInputPins = 0;
            CyParamInfo.GetNumPinsValue(m_edit, out numPins);
            CyStringArrayParamData data;
            CyStringArrayParamData.CreateStringArrayData(m_edit, CyParamInfo.Formal_ParamName_PinTypes, out data);
            for (byte i = 0; i < numPins; i++)
            {
                string pinType = data.GetValue(i);
                if (CyPortConstants.IsInput(pinType) || CyPortConstants.IsBidir(pinType))
                {
                    numInputPins++;
                }
            }
            return numInputPins;
        }

        bool CanBePAPin(int idx)
        {
            CyStringArrayParamData data;
            CyStringArrayParamData.CreateStringArrayData(m_edit, CyParamInfo.Formal_ParamName_PinTypes, out data);
            string pinType = data.GetValue(idx);
            return (CyPortConstants.IsInput(pinType) || CyPortConstants.IsBidir(pinType));
        }

        void m_inEnableModeComboBox_SelectedIndexChanged(object sender, EventArgs e)
        {
            m_edit.SetParamExpr(CyParamInfo.Formal_ParamName_InClkEnableMode, InClkEnableMode);
            m_edit.CommitParamExprs();
        }

        void m_inClockComboBox_SelectedIndexChanged(object sender, EventArgs e)
        {
            bool invert = InvertInClock;
            switch (InputClockIdx)
            {
                case BUS_CLK_IDX:
                    m_edit.SetParamExpr(CyParamInfo.Formal_ParamName_ShowInClkTerm, "false");
                    m_edit.SetParamExpr(CyParamInfo.Formal_ParamName_UsePaInClk, "false");
                    break;
                case EXTERNAL_IDX:
                    m_edit.SetParamExpr(CyParamInfo.Formal_ParamName_ShowInClkTerm, "true");
                    m_edit.SetParamExpr(CyParamInfo.Formal_ParamName_UsePaInClk, "false");
                    break;
                default:
                    m_edit.SetParamExpr(CyParamInfo.Formal_ParamName_ShowInClkTerm, "false");
                    m_edit.SetParamExpr(CyParamInfo.Formal_ParamName_UsePaInClk, "true");
                    PaPin = InputClockIdx;
                    break;
            }

            m_edit.SetParamExpr(CyParamInfo.Formal_ParamName_InvertInClock, invert ? "true" : "false");

            m_edit.CommitParamExprs();
        }

        void m_inClockEnComboBox_SelectedIndexChanged(object sender, EventArgs e)
        {
            bool invert = InvertInClockEn;
            switch (InputClockEnIdx)
            {
                case NONE_IDX:
                    m_edit.SetParamExpr(CyParamInfo.Formal_ParamName_ShowInClkEnTerm, "false");
                    m_edit.SetParamExpr(CyParamInfo.Formal_ParamName_UsePaInClkEn, "false");
                    break;
                case EXTERNAL_IDX:
                    m_edit.SetParamExpr(CyParamInfo.Formal_ParamName_ShowInClkEnTerm, "true");
                    m_edit.SetParamExpr(CyParamInfo.Formal_ParamName_UsePaInClkEn, "false");
                    break;
                default:
                    m_edit.SetParamExpr(CyParamInfo.Formal_ParamName_ShowInClkEnTerm, "false");
                    m_edit.SetParamExpr(CyParamInfo.Formal_ParamName_UsePaInClkEn, "true");
                    PaPin = InputClockEnIdx;
                    break;
            }

            m_edit.SetParamExpr(CyParamInfo.Formal_ParamName_InvertInClockEn, invert ? "true" : "false");

            m_edit.CommitParamExprs();

            m_inEnableModeComboBox.Enabled = InputClockEnIdx != NONE_IDX;
        }

        void m_inResetComboBox_SelectedIndexChanged(object sender, EventArgs e)
        {
            bool invert = InvertInReset;
            switch (InputResetIdx)
            {
                case NONE_IDX:
                    m_edit.SetParamExpr(CyParamInfo.Formal_ParamName_ShowInRstTerm, "false");
                    m_edit.SetParamExpr(CyParamInfo.Formal_ParamName_UsePaInRst, "false");
                    break;
                case EXTERNAL_IDX:
                    m_edit.SetParamExpr(CyParamInfo.Formal_ParamName_ShowInRstTerm, "true");
                    m_edit.SetParamExpr(CyParamInfo.Formal_ParamName_UsePaInRst, "false");
                    break;
                default:
                    m_edit.SetParamExpr(CyParamInfo.Formal_ParamName_ShowInRstTerm, "false");
                    m_edit.SetParamExpr(CyParamInfo.Formal_ParamName_UsePaInRst, "true");
                    PaPin = InputResetIdx;
                    break;
            }

            m_edit.SetParamExpr(CyParamInfo.Formal_ParamName_InvertInReset, invert ? "true" : "false");

            m_edit.CommitParamExprs();
        }

        void m_outputResetCheckBox_CheckedChanged(object sender, EventArgs e)
        {
            m_edit.SetParamExpr(CyParamInfo.Formal_ParamName_OutputResetEnabled, OutputResetEnabled.ToString());
            m_edit.CommitParamExprs();
        }

        void m_oeResetCheckBox_CheckedChanged(object sender, EventArgs e)
        {
            m_edit.SetParamExpr(CyParamInfo.Formal_ParamName_OEResetEnabled, OEResetEnabled.ToString());
            m_edit.CommitParamExprs();
        }

        void m_outEnableModeComboBox_SelectedIndexChanged(object sender, EventArgs e)
        {
            m_edit.SetParamExpr(CyParamInfo.Formal_ParamName_OutClkEnableMode, OutClkEnableMode);
            m_edit.CommitParamExprs();
        }

        void m_outClockComboBox_SelectedIndexChanged(object sender, EventArgs e)
        {
            bool invert = InvertOutClock;
            switch (OutputClockIdx)
            {
                case BUS_CLK_IDX:
                    m_edit.SetParamExpr(CyParamInfo.Formal_ParamName_ShowOutClkTerm, "false");
                    m_edit.SetParamExpr(CyParamInfo.Formal_ParamName_UsePaOutClk, "false");
                    break;
                case EXTERNAL_IDX:
                    m_edit.SetParamExpr(CyParamInfo.Formal_ParamName_ShowOutClkTerm, "true");
                    m_edit.SetParamExpr(CyParamInfo.Formal_ParamName_UsePaOutClk, "false");
                    break;
                default:
                    m_edit.SetParamExpr(CyParamInfo.Formal_ParamName_ShowOutClkTerm, "false");
                    m_edit.SetParamExpr(CyParamInfo.Formal_ParamName_UsePaOutClk, "true");
                    PaPin = OutputClockIdx;
                    break;
            }

            m_edit.SetParamExpr(CyParamInfo.Formal_ParamName_InvertOutClock, invert ? "true" : "false");

            m_edit.CommitParamExprs();
        }

        void m_outClockEnComboBox_SelectedIndexChanged(object sender, EventArgs e)
        {
            bool invert = InvertOutClockEn;
            switch (OutputClockEnIdx)
            {
                case NONE_IDX:
                    m_edit.SetParamExpr(CyParamInfo.Formal_ParamName_ShowOutClkEnTerm, "false");
                    m_edit.SetParamExpr(CyParamInfo.Formal_ParamName_UsePaOutClkEn, "false");
                    break;
                case EXTERNAL_IDX:
                    m_edit.SetParamExpr(CyParamInfo.Formal_ParamName_ShowOutClkEnTerm, "true");
                    m_edit.SetParamExpr(CyParamInfo.Formal_ParamName_UsePaOutClkEn, "false");
                    break;
                default:
                    m_edit.SetParamExpr(CyParamInfo.Formal_ParamName_ShowOutClkEnTerm, "false");
                    m_edit.SetParamExpr(CyParamInfo.Formal_ParamName_UsePaOutClkEn, "true");
                    PaPin = OutputClockEnIdx;
                    break;
            }

            m_edit.SetParamExpr(CyParamInfo.Formal_ParamName_InvertOutClockEn, invert ? "true" : "false");

            m_edit.CommitParamExprs();

            m_outEnableModeComboBox.Enabled = OutputClockEnIdx != NONE_IDX;
        }

        void m_outResetComboBox_SelectedIndexChanged(object sender, EventArgs e)
        {
            bool invert = InvertOutReset;
            switch (OutputResetIdx)
            {
                case NONE_IDX:
                    m_edit.SetParamExpr(CyParamInfo.Formal_ParamName_ShowOutRstTerm, "false");
                    m_edit.SetParamExpr(CyParamInfo.Formal_ParamName_UsePaOutRst, "false");
                    break;
                case EXTERNAL_IDX:
                    m_edit.SetParamExpr(CyParamInfo.Formal_ParamName_ShowOutRstTerm, "true");
                    m_edit.SetParamExpr(CyParamInfo.Formal_ParamName_UsePaOutRst, "false");
                    break;
                default:
                    m_edit.SetParamExpr(CyParamInfo.Formal_ParamName_ShowOutRstTerm, "false");
                    m_edit.SetParamExpr(CyParamInfo.Formal_ParamName_UsePaOutRst, "true");
                    PaPin = OutputResetIdx;
                    break;
            }

            m_edit.SetParamExpr(CyParamInfo.Formal_ParamName_InvertOutReset, invert ? "true" : "false");

            m_edit.CommitParamExprs();
        }

        public bool InvertInClock
        {
            get
            {
                CyPaSelect inClk = m_inClockComboBox.SelectedItem as CyPaSelect;
                return inClk != null && inClk.Invert;
            }
            set
            {
                m_inClockComboBox.SelectedIndexChanged -= m_inClockComboBox_SelectedIndexChanged;
                if (value != InvertInClock || m_inClockComboBox.SelectedItem == null)
                {
                    SelectInClock(InputClockIdx, value);
                }

                m_inClockComboBox.SelectedIndexChanged += m_inClockComboBox_SelectedIndexChanged;
            }
        }

        public bool InvertInClockEn
        {
            get
            {
                CyPaSelect inClkEn = m_inClockEnComboBox.SelectedItem as CyPaSelect;
                return inClkEn != null && inClkEn.Invert;
            }
            set
            {
                m_inClockEnComboBox.SelectedIndexChanged -= m_inClockEnComboBox_SelectedIndexChanged;
                if (value != InvertInClockEn || m_inClockEnComboBox.SelectedItem == null)
                {
                    SelectInClockEn(InputClockEnIdx, value);
                }

                m_inClockEnComboBox.SelectedIndexChanged += m_inClockEnComboBox_SelectedIndexChanged;
            }
        }

        public bool InvertInReset
        {
            get
            {
                CyPaSelect inRst = m_inResetComboBox.SelectedItem as CyPaSelect;
                return inRst != null && inRst.Invert;
            }
            set
            {
                m_inResetComboBox.SelectedIndexChanged -= m_inResetComboBox_SelectedIndexChanged;
                if (value != InvertInReset || m_inResetComboBox.SelectedItem == null)
                {
                    SelectInReset(InputResetIdx, value);
                }

                m_inResetComboBox.SelectedIndexChanged += m_inResetComboBox_SelectedIndexChanged;
            }
        }

        public string InClkEnableMode
        {
            get
            {
                CyEnableType enable = m_inEnableModeComboBox.SelectedItem as CyEnableType;
                return enable == null ? null : enable.ParamValue;
            }
            set
            {
                m_inEnableModeComboBox.SelectedIndexChanged -= m_inEnableModeComboBox_SelectedIndexChanged;
                if (value == null)
                {
                    m_inEnableModeComboBox.SelectedItem = null;
                }
                else
                {
                    switch (value)
                    {
                        case CyPortConstants.ClkEnableModeValue_EDGE:
                            SelectInEnable(CyEnableType.CyEnable.RisingEdge);
                            break;

                        case CyPortConstants.ClkEnableModeValue_LEVEL:
                            SelectInEnable(CyEnableType.CyEnable.Level);
                            break;

                        default:
                            Debug.Fail("unhandled");
                            m_inEnableModeComboBox.SelectedItem = null;
                            break;
                    }
                }
                m_inEnableModeComboBox.SelectedIndexChanged += m_inEnableModeComboBox_SelectedIndexChanged;
            }
        }

        public int InputClockIdx
        {
            get
            {
                CyPaSelect inClk = m_inClockComboBox.SelectedItem as CyPaSelect;
                return inClk == null ? BUS_CLK_IDX : inClk.ClockSelectIdx;
            }
            set
            {
                m_inClockComboBox.SelectedIndexChanged -= m_inClockComboBox_SelectedIndexChanged;
                if (value != InputClockIdx || m_inClockComboBox.SelectedItem == null)
                {
                    SelectInClock(value, InvertInClock);

                    if (value >= 0)
                        PaPin = value;
                }

                m_inClockComboBox.SelectedIndexChanged += m_inClockComboBox_SelectedIndexChanged;
            }
        }

        public int InputClockEnIdx
        {
            get
            {
                CyPaSelect inClkEn = m_inClockEnComboBox.SelectedItem as CyPaSelect;
                return inClkEn == null ? NONE_IDX : inClkEn.ClockSelectIdx;
            }
            set
            {
                m_inClockEnComboBox.SelectedIndexChanged -= m_inClockEnComboBox_SelectedIndexChanged;
                if (value != InputClockEnIdx || m_inClockEnComboBox.SelectedItem == null)
                {
                    SelectInClockEn(value, InvertInClockEn);

                    if (value >= 0)
                        PaPin = value;
                }

                m_inClockEnComboBox.SelectedIndexChanged += m_inClockEnComboBox_SelectedIndexChanged;
            }
        }

        public int InputResetIdx
        {
            get
            {
                CyPaSelect inRst = m_inResetComboBox.SelectedItem as CyPaSelect;
                return inRst == null ? NONE_IDX : inRst.ClockSelectIdx;
            }
            set
            {
                m_inResetComboBox.SelectedIndexChanged -= m_inResetComboBox_SelectedIndexChanged;
                if (value != InputResetIdx || m_inResetComboBox.SelectedItem == null)
                {
                    SelectInReset(value, InvertInReset);

                    if (value >= 0)
                        PaPin = value;
                }

                m_inResetComboBox.SelectedIndexChanged += m_inResetComboBox_SelectedIndexChanged;
            }
        }

        public bool InvertOutClock
        {
            get
            {
                CyPaSelect outClk = m_outClockComboBox.SelectedItem as CyPaSelect;
                return outClk != null && outClk.Invert;
            }
            set
            {
                m_outClockComboBox.SelectedIndexChanged -= m_outClockComboBox_SelectedIndexChanged;
                if (value != InvertOutClock || m_outClockComboBox.SelectedItem == null)
                {
                    SelectOutClock(OutputClockIdx, value);
                }

                m_outClockComboBox.SelectedIndexChanged += m_outClockComboBox_SelectedIndexChanged;
            }
        }

        public bool InvertOutClockEn
        {
            get
            {
                CyPaSelect outClkEn = m_outClockEnComboBox.SelectedItem as CyPaSelect;
                return outClkEn != null && outClkEn.Invert;
            }
            set
            {
                m_outClockEnComboBox.SelectedIndexChanged -= m_outClockEnComboBox_SelectedIndexChanged;
                if (value != InvertOutClockEn || m_outClockEnComboBox.SelectedItem == null)
                {
                    SelectOutClockEn(OutputClockEnIdx, value);
                }

                m_outClockEnComboBox.SelectedIndexChanged += m_outClockEnComboBox_SelectedIndexChanged;
            }
        }

        public bool InvertOutReset
        {
            get
            {
                CyPaSelect outRst = m_outResetComboBox.SelectedItem as CyPaSelect;
                return outRst != null && outRst.Invert;
            }
            set
            {
                m_outResetComboBox.SelectedIndexChanged -= m_outResetComboBox_SelectedIndexChanged;
                if (value != InvertOutReset || m_outResetComboBox.SelectedItem == null)
                {
                    SelectOutReset(OutputResetIdx, value);
                }

                m_outResetComboBox.SelectedIndexChanged += m_outResetComboBox_SelectedIndexChanged;
            }
        }

        public string OutClkEnableMode
        {
            get
            {
                CyEnableType enable = m_outEnableModeComboBox.SelectedItem as CyEnableType;
                return enable == null ? null : enable.ParamValue;
            }
            set
            {
                m_outEnableModeComboBox.SelectedIndexChanged -= m_outEnableModeComboBox_SelectedIndexChanged;
                if (value == null)
                {
                    m_outEnableModeComboBox.SelectedItem = null;
                }
                else
                {
                    switch (value)
                    {
                        case CyPortConstants.ClkEnableModeValue_EDGE:
                            SelectOutEnable(CyEnableType.CyEnable.RisingEdge);
                            break;

                        case CyPortConstants.ClkEnableModeValue_LEVEL:
                            SelectOutEnable(CyEnableType.CyEnable.Level);
                            break;

                        default:
                            Debug.Fail("unhandled");
                            m_outEnableModeComboBox.SelectedItem = null;
                            break;
                    }
                }
                m_outEnableModeComboBox.SelectedIndexChanged += m_outEnableModeComboBox_SelectedIndexChanged;
            }
        }

        public bool OutputResetEnabled
        {
            get
            {
                return m_outputResetCheckBox.CheckState != CheckState.Indeterminate &&
                       m_outputResetCheckBox.Checked;
            }
            set
            {
                m_outputResetCheckBox.CheckedChanged -= m_outputResetCheckBox_CheckedChanged;
                m_outputResetCheckBox.Checked = value;
                m_outputResetCheckBox.CheckedChanged += m_outputResetCheckBox_CheckedChanged;
            }
        }

        public string OutputResetEnabledErrorText
        {
            get { return m_errorProvider.GetError(m_outputResetCheckBox); }
            set { m_errorProvider.SetError(m_outputResetCheckBox, value); }
        }

        public bool OEResetEnabled
        {
            get
            {
                return m_oeResetCheckBox.CheckState != CheckState.Indeterminate &&
                       m_oeResetCheckBox.Checked;
            }
            set
            {
                m_oeResetCheckBox.CheckedChanged -= m_oeResetCheckBox_CheckedChanged;
                m_oeResetCheckBox.Checked = value;
                m_oeResetCheckBox.CheckedChanged += m_oeResetCheckBox_CheckedChanged;
            }
        }

        public string OEResetEnabledErrorText
        {
            get { return m_errorProvider.GetError(m_oeResetCheckBox); }
            set { m_errorProvider.SetError(m_oeResetCheckBox, value); }
        }

        public int OutputClockIdx
        {
            get
            {
                CyPaSelect outClk = m_outClockComboBox.SelectedItem as CyPaSelect;
                return outClk == null ? BUS_CLK_IDX : outClk.ClockSelectIdx;
            }
            set
            {
                m_outClockComboBox.SelectedIndexChanged -= m_outClockComboBox_SelectedIndexChanged;
                if (value != OutputClockIdx || m_outClockComboBox.SelectedItem == null)
                {
                    SelectOutClock(value, InvertOutClock);

                    if (value >= 0)
                        PaPin = value;
                }

                m_outClockComboBox.SelectedIndexChanged += m_outClockComboBox_SelectedIndexChanged;
            }
        }

        public int OutputClockEnIdx
        {
            get
            {
                CyPaSelect outClkEn = m_outClockEnComboBox.SelectedItem as CyPaSelect;
                return outClkEn == null ? NONE_IDX : outClkEn.ClockSelectIdx;
            }
            set
            {
                m_outClockEnComboBox.SelectedIndexChanged -= m_outClockEnComboBox_SelectedIndexChanged;
                if (value != OutputClockEnIdx || m_outClockEnComboBox.SelectedItem == null)
                {
                    SelectOutClockEn(value, InvertOutClockEn);

                    if (value >= 0)
                        PaPin = value;
                }

                m_outClockEnComboBox.SelectedIndexChanged += m_outClockEnComboBox_SelectedIndexChanged;
            }
        }

        public int OutputResetIdx
        {
            get
            {
                CyPaSelect outRst = m_outResetComboBox.SelectedItem as CyPaSelect;
                return outRst == null ? NONE_IDX : outRst.ClockSelectIdx;
            }
            set
            {
                m_outResetComboBox.SelectedIndexChanged -= m_outResetComboBox_SelectedIndexChanged;
                if (value != OutputResetIdx || m_outResetComboBox.SelectedItem == null)
                {
                    SelectOutReset(value, InvertOutReset);

                    if (value >= 0)
                        PaPin = value;
                }

                m_outResetComboBox.SelectedIndexChanged += m_outResetComboBox_SelectedIndexChanged;
            }
        }

        public bool ShowInClkTerm
        {
            get { return InputClockIdx == EXTERNAL_IDX; }
            set
            {
                if (value)
                {
                    InputClockIdx = EXTERNAL_IDX;
                }
                else
                {
                    InputClockIdx = UsePaInClk ? PaPin : BUS_CLK_IDX;
                }
            }
        }

        public bool ShowInClkEnTerm
        {
            get { return InputClockEnIdx == EXTERNAL_IDX; }
            set
            {
                if (value)
                {
                    InputClockEnIdx = EXTERNAL_IDX;
                }
                else
                {
                    InputClockEnIdx = UsePaInClkEn ? PaPin : NONE_IDX;
                }
            }
        }

        public bool ShowInRstTerm
        {
            get { return InputResetIdx == EXTERNAL_IDX; }
            set
            {
                if (value)
                {
                    InputResetIdx = EXTERNAL_IDX;
                }
                else
                {
                    InputResetIdx = UsePaInRst ? PaPin : NONE_IDX;
                }
            }
        }

        public bool ShowOutClkTerm
        {
            get { return OutputClockIdx == EXTERNAL_IDX; }
            set
            {
                if (value)
                {
                    OutputClockIdx = EXTERNAL_IDX;
                }
                else
                {
                    OutputClockIdx = UsePaOutClk ? PaPin : BUS_CLK_IDX;
                }
            }
        }

        public bool ShowOutClkEnTerm
        {
            get { return OutputClockEnIdx == EXTERNAL_IDX; }
            set
            {
                if (value)
                {
                    OutputClockEnIdx = EXTERNAL_IDX;
                }
                else
                {
                    OutputClockEnIdx = UsePaOutClkEn ? PaPin : NONE_IDX;
                }
            }
        }

        public bool ShowOutRstTerm
        {
            get { return OutputResetIdx == EXTERNAL_IDX; }
            set
            {
                if (value)
                {
                    OutputResetIdx = EXTERNAL_IDX;
                }
                else
                {
                    OutputResetIdx = UsePaOutRst ? PaPin : NONE_IDX;
                }
            }
        }

        public bool UsePaInClk
        {
            get { return InputClockIdx >= 0; }
            set
            {
                if (value)
                {
                    InputClockIdx = PaPin;
                }
                else
                {
                    InputClockIdx = ShowInClkTerm ? EXTERNAL_IDX : BUS_CLK_IDX;
                }
            }
        }

        public bool UsePaInClkEn
        {
            get { return InputClockEnIdx >= 0; }
            set
            {
                if (value)
                {
                    InputClockEnIdx = PaPin;
                }
                else
                {
                    InputClockEnIdx = ShowInClkEnTerm ? EXTERNAL_IDX : NONE_IDX;
                }
            }
        }

        public bool UsePaInRst
        {
            get { return InputResetIdx >= 0; }
            set
            {
                if (value)
                {
                    InputResetIdx = PaPin;
                }
                else
                {
                    InputResetIdx = ShowInRstTerm ? EXTERNAL_IDX : NONE_IDX;
                }
            }
        }

        public bool UsePaOutClk
        {
            get { return OutputClockIdx >= 0; }
            set
            {
                if (value)
                {
                    OutputClockIdx = PaPin;
                }
                else
                {
                    OutputClockIdx = ShowOutClkTerm ? EXTERNAL_IDX : BUS_CLK_IDX;
                }
            }
        }

        public bool UsePaOutClkEn
        {
            get { return OutputClockEnIdx >= 0; }
            set
            {
                if (value)
                {
                    OutputClockEnIdx = PaPin;
                }
                else
                {
                    OutputClockEnIdx = ShowOutClkEnTerm ? EXTERNAL_IDX : NONE_IDX;
                }
            }
        }

        public bool UsePaOutRst
        {
            get { return OutputResetIdx >= 0; }
            set
            {
                if (value)
                {
                    OutputResetIdx = PaPin;
                }
                else
                {
                    OutputResetIdx = ShowOutRstTerm ? EXTERNAL_IDX : NONE_IDX;
                }
            }
        }

        public int PaPin
        {
            get { return m_paPin; }
            set
            {
                bool changed = m_paPin != value;
                m_paPin = value;
                if (changed && value >= 0)
                {
                    m_edit.SetParamExpr(CyParamInfo.Formal_ParamName_PaPin, PaPin.ToString());
                    m_edit.CommitParamExprs();

                    // go set the PA Pin for any of the 6 that were using the PA pin
                    if (OutputClockIdx >= 0)
                        OutputClockIdx = value;
                    if (OutputClockEnIdx >= 0)
                        OutputClockEnIdx = value;
                    if (OutputResetIdx >= 0)
                        OutputResetIdx = value;
                    if (InputClockIdx >= 0)
                        InputClockIdx = value;
                    if (InputClockEnIdx >= 0)
                        InputClockEnIdx = value;
                    if (InputResetIdx >= 0)
                        InputResetIdx = value;
                }
                else if (changed && value == -1)
                {
                    m_edit.SetParamExpr(CyParamInfo.Formal_ParamName_UsePaInClk, "false");
                    m_edit.SetParamExpr(CyParamInfo.Formal_ParamName_UsePaInClkEn, "false");
                    m_edit.SetParamExpr(CyParamInfo.Formal_ParamName_UsePaInRst, "false");
                    m_edit.SetParamExpr(CyParamInfo.Formal_ParamName_UsePaOutClk, "false");
                    m_edit.SetParamExpr(CyParamInfo.Formal_ParamName_UsePaOutClkEn, "false");
                    m_edit.SetParamExpr(CyParamInfo.Formal_ParamName_UsePaOutRst, "false");
                    m_edit.CommitParamExprs();
                    //InputClockIdx = NONE_IDX;
                    //UsePaInClk = false;
                    //InputClockEnIdx = NONE_IDX;
                    //UsePaInClkEn = false;
                    //InputResetIdx = NONE_IDX;
                    //UsePaInRst = false;
                    //OutputClockIdx = NONE_IDX;
                    //UsePaOutClk = false;
                    //OutputClockEnIdx = NONE_IDX;
                    //UsePaOutClkEn = false;
                    //OutputResetIdx = NONE_IDX;
                    //UsePaOutRst = false;
                }
            }
        }

        internal void UpdateFromExprs()
        {
            // use inClock DropDown as reference for how many possible PA pins we had before.
            int oldNumCanBePAPins = m_inClockComboBox.Items.Count/2 - 2;
            if (oldNumCanBePAPins != GetNumCanBePAPins())
            {
                ClearDropDowns();
                PopulateDropDowns();
            }

            string value;
            CyPortCustomizer.GetParamValue(m_edit, CyParamInfo.Formal_ParamName_OutClkEnableMode, out value);
            OutClkEnableMode = value;

            CyPortCustomizer.GetParamValue(m_edit, CyParamInfo.Formal_ParamName_InClkEnableMode, out value);
            InClkEnableMode = value;

            int paPin;
            CyPortCustomizer.GetParamValue(m_edit, CyParamInfo.Formal_ParamName_PaPin, out paPin);
            if (paPin >= 0 && CanBePAPin(paPin))
                PaPin = paPin;
            else
                PaPin = -1;

            bool boolVal;
            CyPortCustomizer.GetParamValue(m_edit, CyParamInfo.Formal_ParamName_OutputResetEnabled, out boolVal);
            OutputResetEnabled = boolVal;

            CyPortCustomizer.GetParamValue(m_edit, CyParamInfo.Formal_ParamName_OEResetEnabled, out boolVal);
            OEResetEnabled = boolVal;

            CyPortCustomizer.GetParamValue(m_edit, CyParamInfo.Formal_ParamName_ShowInClkTerm, out boolVal);
            ShowInClkTerm = boolVal;

            CyPortCustomizer.GetParamValue(m_edit, CyParamInfo.Formal_ParamName_ShowInClkEnTerm, out boolVal);
            ShowInClkEnTerm = boolVal;

            CyPortCustomizer.GetParamValue(m_edit, CyParamInfo.Formal_ParamName_ShowInRstTerm, out boolVal);
            ShowInRstTerm = boolVal;

            CyPortCustomizer.GetParamValue(m_edit, CyParamInfo.Formal_ParamName_ShowOutClkTerm, out boolVal);
            ShowOutClkTerm = boolVal;

            CyPortCustomizer.GetParamValue(m_edit, CyParamInfo.Formal_ParamName_ShowOutClkEnTerm, out boolVal);
            ShowOutClkEnTerm = boolVal;

            CyPortCustomizer.GetParamValue(m_edit, CyParamInfo.Formal_ParamName_ShowOutRstTerm, out boolVal);
            ShowOutRstTerm = boolVal;

            CyPortCustomizer.GetParamValue(m_edit, CyParamInfo.Formal_ParamName_UsePaInClk, out boolVal);
            UsePaInClk = boolVal;

            CyPortCustomizer.GetParamValue(m_edit, CyParamInfo.Formal_ParamName_UsePaInClkEn, out boolVal);
            UsePaInClkEn = boolVal;

            CyPortCustomizer.GetParamValue(m_edit, CyParamInfo.Formal_ParamName_UsePaInRst, out boolVal);
            UsePaInRst = boolVal;

            CyPortCustomizer.GetParamValue(m_edit, CyParamInfo.Formal_ParamName_UsePaOutClk, out boolVal);
            UsePaOutClk = boolVal;

            CyPortCustomizer.GetParamValue(m_edit, CyParamInfo.Formal_ParamName_UsePaOutClkEn, out boolVal);
            UsePaOutClkEn = boolVal;

            CyPortCustomizer.GetParamValue(m_edit, CyParamInfo.Formal_ParamName_UsePaOutRst, out boolVal);
            UsePaOutRst = boolVal;

            CyPortCustomizer.GetParamValue(m_edit, CyParamInfo.Formal_ParamName_InvertInClock, out boolVal);
            InvertInClock = boolVal;

            CyPortCustomizer.GetParamValue(m_edit, CyParamInfo.Formal_ParamName_InvertInClockEn, out boolVal);
            InvertInClockEn = boolVal;

            CyPortCustomizer.GetParamValue(m_edit, CyParamInfo.Formal_ParamName_InvertInReset, out boolVal);
            InvertInReset = boolVal;

            CyPortCustomizer.GetParamValue(m_edit, CyParamInfo.Formal_ParamName_InvertOutClock, out boolVal);
            InvertOutClock = boolVal;

            CyPortCustomizer.GetParamValue(m_edit, CyParamInfo.Formal_ParamName_InvertOutClockEn, out boolVal);
            InvertOutClockEn = boolVal;

            CyPortCustomizer.GetParamValue(m_edit, CyParamInfo.Formal_ParamName_InvertOutReset, out boolVal);
            InvertOutReset = boolVal;
        }
               

        void SelectInEnable(CyEnableType.CyEnable enable)
        {
            foreach (CyEnableType enb in m_inEnableModeComboBox.Items)
            {
                if (enb.Enable == enable)
                {
                    m_inEnableModeComboBox.SelectedItem = enb;
                    break;
                }
            }
        }

        void SelectInClock(int clkIdx, bool invert)
        {
            foreach (CyPaSelect clk in m_inClockComboBox.Items)
            {
                if (clk.ClockSelectIdx == clkIdx && clk.Invert == invert)
                {
                    m_inClockComboBox.SelectedItem = clk;
                    break;
                }
            }
        }

        void SelectInClockEn(int clkIdx, bool invert)
        {
            foreach (CyPaSelect clk in m_inClockEnComboBox.Items)
            {
                if (clk.ClockSelectIdx == clkIdx && clk.Invert == invert)
                {
                    m_inClockEnComboBox.SelectedItem = clk;
                    break;
                }
            }
        }

        void SelectInReset(int clkIdx, bool invert)
        {
            foreach (CyPaSelect clk in m_inResetComboBox.Items)
            {
                if (clk.ClockSelectIdx == clkIdx && clk.Invert == invert)
                {
                    m_inResetComboBox.SelectedItem = clk;
                    break;
                }
            }
        }

        void SelectOutEnable(CyEnableType.CyEnable enable)
        {
            foreach (CyEnableType enb in m_outEnableModeComboBox.Items)
            {
                if (enb.Enable == enable)
                {
                    m_outEnableModeComboBox.SelectedItem = enb;
                    break;
                }
            }
        }

        void SelectOutClock(int clkIdx, bool invert)
        {
            foreach (CyPaSelect clk in m_outClockComboBox.Items)
            {
                if (clk.ClockSelectIdx == clkIdx && clk.Invert == invert)
                {
                    m_outClockComboBox.SelectedItem = clk;
                    break;
                }
            }
        }

        void SelectOutClockEn(int clkIdx, bool invert)
        {
            foreach (CyPaSelect clk in m_outClockEnComboBox.Items)
            {
                if (clk.ClockSelectIdx == clkIdx && clk.Invert == invert)
                {
                    m_outClockEnComboBox.SelectedItem = clk;
                    break;
                }
            }
        }

        void SelectOutReset(int clkIdx, bool invert)
        {
            foreach (CyPaSelect clk in m_outResetComboBox.Items)
            {
                if (clk.ClockSelectIdx == clkIdx && clk.Invert == invert)
                {
                    m_outResetComboBox.SelectedItem = clk;
                    break;
                }
            }
        }

        public ICyInstEdit_v1 Edit
        {
            get { return m_edit; }
            set
            {
                m_edit = value;
                UpdateFromExprs();
            }
        }

        #region ICyParamEditingControl Members

        public Control DisplayControl
        {
            get { return this; }
        }

        public IEnumerable<CyCustErr> GetErrors()
        {
            List<CyCustErr> errs = new List<CyCustErr>();

            foreach (string paramName in m_edit.GetParamNames())
            {
                CyCompDevParam param = m_edit.GetCommittedParam(paramName);
                if (param.TabName == CyCustomizer.ResetTabName)
                {
                    if (param.ErrorCount > 0)
                    {
                        foreach (string errMsg in param.Errors)
                        {
                            errs.Add(new CyCustErr(errMsg));
                        }
                    }
                }
            }

            return errs;
        }

        #endregion
    }

    class CyPaSelect
    {
        private int m_clockSelectIdx;
        private bool m_invert;
        private ICyInstQuery_v1 m_instQuery;

        public int ClockSelectIdx { get { return m_clockSelectIdx; } }

        public bool Invert { get { return m_invert; } }

        public CyPaSelect(int clockSelectIdx, bool invert, ICyInstQuery_v1 instQuery)
        {
            m_clockSelectIdx = clockSelectIdx;
            m_invert = invert;
            m_instQuery = instQuery;
        }

        public override string ToString()
        {
            string name;
            switch (ClockSelectIdx)
            {
                case CyClockingControl.NONE_IDX:
                    name = "None";
                    break;
                case CyClockingControl.BUS_CLK_IDX:
                    name = m_instQuery.DeviceQuery.IsPSoC4 ? "HFCLK" : "BUS_CLK";
                    break;
                case CyClockingControl.EXTERNAL_IDX:
                    name = "External";
                    break;
                default:
                    byte numPins;
                    CyCustErr err = CyParamInfo.GetNumPinsValue(m_instQuery, out numPins);
                    if (err.IsOk && ClockSelectIdx >= 0 && ClockSelectIdx < numPins)
                    {
                        name = CyPortCustomizer.GetPinPoundDefineName(m_instQuery, ClockSelectIdx);
                    }
                    else
                    {
                        Debug.Fail("unhandled");
                        name = base.ToString();
                    }
                    break;
            }
            if (Invert)
                name += " (inverted)";

            return name;
        }
    }

    class CyEnableType
    {
        public enum CyEnable { RisingEdge, Level };

        CyEnable m_enable;

        public CyEnable Enable { get { return m_enable; } }

        public CyEnableType(CyEnable enable)
        {
            m_enable = enable;
        }

        public string ParamValue
        {
            get
            {
                switch (Enable)
                {
                    case CyEnable.RisingEdge:
                        return CyPortConstants.ClkEnableModeValue_EDGE;

                    case CyEnable.Level:
                        return CyPortConstants.ClkEnableModeValue_LEVEL;

                    default:
                        Debug.Fail("unhandled");
                        return string.Empty;
                }
            }
        }

        public override string ToString()
        {
            switch (Enable)
            {
                case CyEnable.RisingEdge:
                    return "Rising Edge";

                case CyEnable.Level:
                    return "Level";

                default:
                    Debug.Fail("unhandled");
                    return base.ToString();
            }
        }
    }
}
