/*******************************************************************************
* Copyright 2008-2014, Cypress Semiconductor Corporation. All rights reserved.
* You may use this file only in accordance with the license, terms, conditions, 
* disclaimers, and limitations in the end user license agreement accompanying 
* the software package with which this file was provided.
********************************************************************************/

using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Drawing;
using System.Diagnostics;
using System.Data;
using System.Text;
using System.Windows.Forms;
using CyDesigner.Extensions.Common;
using CyDesigner.Extensions.Gde;

namespace Counter_v3_0
{
    public partial class CyCounterControl : UserControl
    {
        ICyInstEdit_v1 m_component = null;
        ICyTerminalQuery_v1 m_termQuery = null;
        CyCounterControlAdv m_control_adv;
        CyCounterParameters m_params;
        const string emptyStr = "";
        const string CLOCK = "clock";
        const string COUNT = "count";
        const string CLOCKWITHUPDOWN = "2";
        const string DOWNCOUNTER = "3";
        private int m_value = -1;

        public CyCounterControl(ICyInstEdit_v1 inst, ICyTerminalQuery_v1 termQuery,
                                CyCounterControlAdv control_advanced, CyCounterParameters parameters)
        {
            m_component = inst;
            m_params = parameters;
            m_termQuery = termQuery;
            m_control_adv = control_advanced;
            InitializeComponent();
            InitializeFormComponents(inst);
            UpdateFormFromParams(m_component);
        }
        ///// <summary>
        ///// Need to add detection of when the parent form is closing allowing me to cancel if there are errors in the 
        ///// parameters
        ///// Also need to handle CyNumericUpDowns to override the UpButton and DownButtons before the value is changed
        ///// </summary>
        protected override void OnCreateControl()
        {
            base.OnCreateControl();
        }

        private void InitializeFormComponents(ICyInstEdit_v1 inst)
        {
            //Initialize Clock Mode Combo Box with Enumerated Types
            //Set the Clock Modes Combo Box from Enums
            IEnumerable<string> ClockModeEnums = inst.GetPossibleEnumValues(CyCounterParameters.CLOCKMODE);
            foreach (string str in ClockModeEnums)
            {
                m_cbClockMode.Items.Add(str);
            }

            //Initialize Compare Mode Combo Box with Enumerated Types
            //Set the Compare Modes Combo Box from Enums
            IEnumerable<string> CompareModeEnums = inst.GetPossibleEnumValues(CyCounterParameters.COMPAREMODE);
            foreach (string str in CompareModeEnums)
            {
                m_cbCompareMode.Items.Add(str);
            }
            m_numPeriod.Minimum = Decimal.MinValue;
            m_numPeriod.Maximum = Decimal.MaxValue;
            m_numCompare1.Minimum = Decimal.MinValue;
            m_numCompare1.Maximum = Decimal.MaxValue;
        }

        void UnhookUpdateEvents()
        {
            //First remove event handler to keep from attaching multiple
            m_numPeriod.UpEvent -= new UpButtonEvent(m_numPeriod_UpEvent);
            m_numPeriod.DownEvent -= new DownButtonEvent(m_numPeriod_DownEvent);
            m_numCompare1.UpEvent -= new UpButtonEvent(m_numCompare1_UpEvent);
            m_numCompare1.DownEvent -= new DownButtonEvent(m_numCompare1_DownEvent); ;
            m_numCompare1.ValueChanged -= m_numCompare1_ValueChanged;
            m_numPeriod.ValueChanged -= m_numPeriod_ValueChanged;
        }

        void HookupUpdateEvents()
        {
            //Now attach the event handler 
            m_numPeriod.UpEvent += new UpButtonEvent(m_numPeriod_UpEvent);
            m_numPeriod.DownEvent += new DownButtonEvent(m_numPeriod_DownEvent);
            m_numCompare1.UpEvent += new UpButtonEvent(m_numCompare1_UpEvent);
            m_numCompare1.DownEvent += new DownButtonEvent(m_numCompare1_DownEvent);
            m_numCompare1.ValueChanged += m_numCompare1_ValueChanged;
            m_numPeriod.ValueChanged += m_numPeriod_ValueChanged;
        }

        public void UpdateFormFromParams(ICyInstEdit_v1 inst)
        {
            UnhookUpdateEvents();
            m_params.GetParams();

            switch (m_params.m_resolution.Value)
            {
                case "8": m_rbResolution8.Checked = true; break;
                case "16": m_rbResolution16.Checked = true; break;
                case "24": m_rbResolution24.Checked = true; break;
                case "32": m_rbResolution32.Checked = true; break;
                default: Debug.Fail(CyCounterParameters.UNHANDLED_CASE); break;
            }

            m_numPeriod.Value = Convert.ToInt64(m_params.m_period.Value);
            switch (m_params.m_fixedFunction.Value)
            {
                case CyCounterParameters.TRUE:
                    m_rbFixedFunction.Checked = true;
                    m_rbUDB.Checked = false;
                    break;
                case CyCounterParameters.FALSE:
                    m_rbUDB.Checked = true;
                    m_rbFixedFunction.Checked = false;
                    break;
                default: Debug.Fail(CyCounterParameters.UNHANDLED_CASE); break;
            }

            //Set Compare Value numeric up down
            m_numCompare1.Value = Convert.ToInt64(m_params.m_compareValue.Value);

            ////Set the Clock Modes Combo Box from Enums            
            string displayName = null;
            CyCustErr err = CyCounterParameters.GetClockModeValue(inst, out displayName);
            if (m_cbClockMode.Items.Contains(displayName))
            {
                m_cbClockMode.SelectedItem = displayName;
            }
            string errMsg = (err.IsOk) ? string.Empty : err.Message;
            ep_Errors.SetError(m_cbClockMode, errMsg);
            //Set the Compare Modes Combo Box from Enums  
            string paramName = null;
            CyCustErr error = CyCounterParameters.GetCompareModeValue(inst, out paramName);
            if (m_cbCompareMode.Items.Contains(paramName))
            {
                m_cbCompareMode.SelectedItem = paramName;
            }
            string errorMsg = (error.IsOk) ? string.Empty : error.Message;
            ep_Errors.SetError(m_cbCompareMode, errorMsg);

            switch (m_params.m_fixedFunction.Value)
            {
                case CyCounterParameters.TRUE: SetFixedFunction(); break;
                case CyCounterParameters.FALSE: ClearFixedFunction(); break;
                default: Debug.Fail(CyCounterParameters.UNHANDLED_CASE); break;
            }
            HookupUpdateEvents();
        }

        private void SetFixedFunction()
        {
            if (m_rbResolution24.Checked || m_rbResolution32.Checked)
                m_rbResolution16_Click(this, EventArgs.Empty);
            m_rbResolution32.Enabled = false;
            m_rbResolution24.Enabled = false;
            string prm = m_component.ResolveEnumDisplayToId(CyCounterParameters.CLOCKMODE,
                                                            CyCounterParameters.ClockModeEnumID_DownCounter);
            string clockMode = m_component.GetCommittedParam(CyCounterParameters.CLOCKMODE).Value;
            if (clockMode != DOWNCOUNTER)
            {
                m_params.SetAParameter(CyCounterParameters.CLOCKMODE, prm);
            }
            m_cbClockMode.SelectedItem = CyCounterParameters.ClockModeEnumID_DownCounter;
            m_cbClockMode.Enabled = false;
            m_cbCompareMode.Enabled = false;
            m_bMaxCompareValue.Enabled = false;
            m_numCompare1.Enabled = false;
            string interruptOnCapture = m_component.GetCommittedParam(CyCounterParameters.INTERRUPT_ON_CAPTURE).Value;
            if (interruptOnCapture != CyCounterParameters.FALSE)
            {
                m_params.SetAParameter(CyCounterParameters.INTERRUPT_ON_CAPTURE, CyCounterParameters.FALSE);
            }
        }

        private void ClearFixedFunction()
        {
            //Enable 24 and 32-bit functionality
            m_rbResolution32.Enabled = true;
            m_rbResolution24.Enabled = true;
            m_cbClockMode.Enabled = true;
            m_cbCompareMode.Enabled = true;
            m_bMaxCompareValue.Enabled = true;
            m_numCompare1.Enabled = true;
        }

        private void m_numPeriod_ValueChanged(object sender, EventArgs e)
        {
            CancelEventArgs ce = new CancelEventArgs();

            m_numPeriod_Validating(sender, ce);
            if (!ce.Cancel)
            {
                m_params.SetAParameter(CyCounterParameters.PERIOD, m_numPeriod.Value.ToString() + "u");
                if (m_cbClockMode.SelectedIndex == 2 || m_cbClockMode.SelectedIndex == 3)
                    m_numCompare1.Maximum = m_numPeriod.Value;
                else if (m_rbResolution8.Checked)
                    m_numCompare1.Maximum = Counter_v3_0.CyCounterParameters.CONST_2_8;
                else if (m_rbResolution16.Checked)
                    m_numCompare1.Maximum = Counter_v3_0.CyCounterParameters.CONST_2_16;
                else if (m_rbResolution24.Checked)
                    m_numCompare1.Maximum = Counter_v3_0.CyCounterParameters.CONST_2_24;
                else
                    m_numCompare1.Maximum = Counter_v3_0.CyCounterParameters.CONST_2_32;
            }
        }

        private void m_rbResolution8_Click(object sender, MouseEventArgs e)
        {
            if (!m_rbResolution8.Checked)
            {
                m_rbResolution8.Checked = true;
                m_rbResolution16.Checked = false;
                m_rbResolution24.Checked = false;
                m_rbResolution32.Checked = false;
                m_params.SetAParameter(CyCounterParameters.RESOLUTION, CyCounterParameters.EIGHT_BIT);
            }
            m_numPeriod_Validating(sender, new CancelEventArgs());
            m_numCompare1_Validating(sender, new CancelEventArgs());
        }

        private void m_rbResolution16_Click(object sender, EventArgs e)
        {
            if (!m_rbResolution16.Checked)
            {
                m_rbResolution8.Checked = false;
                m_rbResolution16.Checked = true;
                m_rbResolution24.Checked = false;
                m_rbResolution32.Checked = false;
                m_params.SetAParameter(CyCounterParameters.RESOLUTION, CyCounterParameters.SIXTEEN_BIT);
            }
            m_numPeriod_Validating(sender, new CancelEventArgs());
            m_numCompare1_Validating(sender, new CancelEventArgs());
        }

        private void m_rbResolution24_Click(object sender, EventArgs e)
        {
            if (!m_rbResolution24.Checked)
            {
                m_rbResolution8.Checked = false;
                m_rbResolution16.Checked = false;
                m_rbResolution24.Checked = true;
                m_rbResolution32.Checked = false;
                m_params.SetAParameter(CyCounterParameters.RESOLUTION, CyCounterParameters.TWENTYFOUR_BIT);
            }
            m_numPeriod_Validating(sender, new CancelEventArgs());
            m_numCompare1_Validating(sender, new CancelEventArgs());
        }

        private void m_rbResolution32_Click(object sender, EventArgs e)
        {
            if (!m_rbResolution32.Checked)
            {
                m_rbResolution8.Checked = false;
                m_rbResolution16.Checked = false;
                m_rbResolution24.Checked = false;
                m_rbResolution32.Checked = true;
                m_params.SetAParameter(CyCounterParameters.RESOLUTION, CyCounterParameters.THIRTYTWO_BIT);
            }
            m_numPeriod_Validating(sender, new CancelEventArgs());
            m_numCompare1_Validating(sender, new CancelEventArgs());

        }

        private void m_rbFixedFunction_Click(object sender, EventArgs e)
        {
            m_rbFixedFunction.Checked = true;
            m_rbUDB.Checked = false;
            m_value = m_cbClockMode.SelectedIndex;
            SetFixedFunction();
            m_params.SetAParameter(CyCounterParameters.FIXEDFUNCTION, CyCounterParameters.TRUE);
            UpdateAdvancedForm();
        }

        private void m_rbUDB_Click(object sender, EventArgs e)
        {
            m_rbFixedFunction.Checked = false;
            m_rbUDB.Checked = true;
            if (m_value >= 0) // set previous value if it was reset by FixedFunction mode
                m_cbClockMode.SelectedIndex = m_value;
            ClearFixedFunction();
            m_params.SetAParameter(CyCounterParameters.FIXEDFUNCTION, CyCounterParameters.FALSE);
            UpdateAdvancedForm();
        }

        private void m_bMaxPeriod_Click(object sender, EventArgs e)
        {
            if (m_rbResolution8.Checked)
                m_numPeriod.Value = m_cbClockMode.SelectedIndex > 1 ? Counter_v3_0.CyCounterParameters.CONST_2_8 :
                    Counter_v3_0.CyCounterParameters.CONST_2_8 - 1;
            else if (m_rbResolution16.Checked)
                m_numPeriod.Value = m_cbClockMode.SelectedIndex > 1 ? Counter_v3_0.CyCounterParameters.CONST_2_16 :
                    Counter_v3_0.CyCounterParameters.CONST_2_16 - 1;
            else if (m_rbResolution24.Checked)
                m_numPeriod.Value = m_cbClockMode.SelectedIndex > 1 ? Counter_v3_0.CyCounterParameters.CONST_2_24 :
                    Counter_v3_0.CyCounterParameters.CONST_2_24 - 1;
            else
                m_numPeriod.Value = m_cbClockMode.SelectedIndex > 1 ? Counter_v3_0.CyCounterParameters.CONST_2_32 :
                    Counter_v3_0.CyCounterParameters.CONST_2_32 - 1;
        }

        private void m_bMaxCompareValue_Click(object sender, EventArgs e)
        {
            if (m_cbClockMode.SelectedIndex == 2 || m_cbClockMode.SelectedIndex == 3)
                m_numCompare1.Value = m_numPeriod.Value;
            else if (m_rbResolution8.Checked)
            {
                m_numCompare1.Maximum = Counter_v3_0.CyCounterParameters.CONST_2_8;
                m_numCompare1.Value = Counter_v3_0.CyCounterParameters.CONST_2_8;
            }
            else if (m_rbResolution16.Checked)
            {
                m_numCompare1.Maximum = Counter_v3_0.CyCounterParameters.CONST_2_16;
                m_numCompare1.Value = Counter_v3_0.CyCounterParameters.CONST_2_16;
            }
            else if (m_rbResolution24.Checked)
            {
                m_numCompare1.Maximum = Counter_v3_0.CyCounterParameters.CONST_2_24;
                m_numCompare1.Value = Counter_v3_0.CyCounterParameters.CONST_2_24;
            }
            else
            {
                m_numCompare1.Maximum = Counter_v3_0.CyCounterParameters.CONST_2_32;
                m_numCompare1.Value = Counter_v3_0.CyCounterParameters.CONST_2_32;
            }
        }

        private void m_numCompare1_ValueChanged(object sender, EventArgs e)
        {
            CancelEventArgs ce = new CancelEventArgs();
            m_numCompare1_Validating(sender, ce);
            if (!ce.Cancel)
            {
                m_params.SetAParameter(CyCounterParameters.COMPAREVALUE,
                    m_numCompare1.Value.ToString() + CyCounterParameters.UNIT);
            }
        }

        private void UpdateAdvancedForm()
        {
            if (m_control_adv != null)
                m_control_adv.UpdateFormFromParams(m_component);
        }

        private void m_cbClockMode_SelectedIndexChanged(object sender, EventArgs e)
        {
            string prm = m_component.ResolveEnumDisplayToId(CyCounterParameters.CLOCKMODE, m_cbClockMode.Text);
            m_params.SetAParameter(CyCounterParameters.CLOCKMODE, prm);

            if (m_cbClockMode.SelectedIndex == 2 || m_cbClockMode.SelectedIndex == 3)
            {
                if (m_numCompare1.Value > m_numPeriod.Value)
                    m_numCompare1.Value = m_numPeriod.Value;
            }
            m_numPeriod_Validating(sender, new CancelEventArgs());
        }

        private void m_cbCompareMode_SelectedIndexChanged(object sender, EventArgs e)
        {
            string prm = m_component.ResolveEnumDisplayToId(CyCounterParameters.COMPAREMODE, m_cbCompareMode.Text);
            m_params.SetAParameter(CyCounterParameters.COMPAREMODE, prm);
        }

        private void m_numPeriod_Validating(object sender, CancelEventArgs e)
        {
            if (m_numPeriod != null)
            {
                if (m_rbResolution8.Checked)
                {
                    if (((m_numPeriod.Value < 0) || (m_numPeriod.Value > CyCounterParameters.CONST_2_8)) &&
                        m_cbClockMode.SelectedIndex > 1)
                    {
                        ep_Errors.SetError(m_numPeriod, string.Format(Resources.PeriodErrorProvider, 8, 0,
                            CyCounterParameters.CONST_2_8));
                        e.Cancel = true;
                    }
                    else if (((m_numPeriod.Value < 1) || (m_numPeriod.Value > CyCounterParameters.CONST_2_8 - 1)) &&
                        m_cbClockMode.SelectedIndex <= 1)
                    {
                        ep_Errors.SetError(m_numPeriod, string.Format(Resources.PeriodErrorProvider, 8, 1,
                                      CyCounterParameters.CONST_2_8 - 1));
                        e.Cancel = true;
                    }
                    else
                    {
                        ep_Errors.SetError(m_numPeriod, string.Empty);
                    }
                }
                if (m_rbResolution16.Checked)
                {
                    if (((m_numPeriod.Value < 0) || (m_numPeriod.Value > CyCounterParameters.CONST_2_16)) &&
                        m_cbClockMode.SelectedIndex > 1)
                    {
                        ep_Errors.SetError(m_numPeriod, string.Format(Resources.PeriodErrorProvider, 16, 0,
                                          CyCounterParameters.CONST_2_16));
                        e.Cancel = true;
                    }
                    else if (((m_numPeriod.Value < 1) || (m_numPeriod.Value > CyCounterParameters.CONST_2_16 - 1)) &&
                        m_cbClockMode.SelectedIndex <= 1)
                    {
                        ep_Errors.SetError(m_numPeriod, string.Format(Resources.PeriodErrorProvider, 16, 1,
                                          CyCounterParameters.CONST_2_16 - 1));
                        e.Cancel = true;
                    }
                    else
                    {
                        ep_Errors.SetError(m_numPeriod, string.Empty);
                    }
                }
                if (m_rbResolution24.Checked)
                {
                    if (((m_numPeriod.Value < 0) || (m_numPeriod.Value > CyCounterParameters.CONST_2_24)) &&
                        m_cbClockMode.SelectedIndex > 1)
                    {
                        ep_Errors.SetError(m_numPeriod, string.Format(Resources.PeriodErrorProvider, 24, 0,
                                           CyCounterParameters.CONST_2_24));
                        e.Cancel = true;
                    }
                    else if (((m_numPeriod.Value < 1) || (m_numPeriod.Value > CyCounterParameters.CONST_2_24 - 1)) &&
                        m_cbClockMode.SelectedIndex <= 1)
                    {
                        ep_Errors.SetError(m_numPeriod, string.Format(Resources.PeriodErrorProvider, 24, 1,
                                           CyCounterParameters.CONST_2_24 - 1));
                        e.Cancel = true;
                    }
                    else
                    {
                        ep_Errors.SetError(m_numPeriod, string.Empty);
                    }
                }
                if (m_rbResolution32.Checked)
                {
                    if (((m_numPeriod.Value < 0) || (m_numPeriod.Value > CyCounterParameters.CONST_2_32)) &&
                        m_cbClockMode.SelectedIndex > 1)
                    {
                        ep_Errors.SetError(m_numPeriod, string.Format(Resources.PeriodErrorProvider, 32, 0,
                                           CyCounterParameters.CONST_2_32));
                        e.Cancel = true;
                    }
                    if (((m_numPeriod.Value < 1) || (m_numPeriod.Value > CyCounterParameters.CONST_2_32 - 1)) &&
                        m_cbClockMode.SelectedIndex <= 1)
                    {
                        ep_Errors.SetError(m_numPeriod, string.Format(Resources.PeriodErrorProvider, 32, 1,
                                           CyCounterParameters.CONST_2_32 - 1));
                        e.Cancel = true;
                    }
                    else
                    {
                        ep_Errors.SetError(m_numPeriod, string.Empty);
                    }
                }
            }
            else
            {
                ep_Errors.SetError(m_numPeriod, "Must be a valid value");
            }
        }

        /// <summary>
        /// This event is called when the down button is pressed and before the value is decremented
        /// It allows me to see if I'm at my internal minimum and cancel the increment if I don't want it to happen
        /// </summary>
        /// <param name="sender"></param>
        /// <param name="e"></param>        
        void m_numPeriod_DownEvent(object sender, CyDownButtonEventArgs e)
        {
            if (m_numPeriod.Value == 0)
            {
                e.m_cancel = true;
                return;
            }
        }
        private void m_numPeriod_KeyUp(object sender, KeyEventArgs e)
        {
            m_numPeriod_Validating(sender, new CancelEventArgs());

        }

        /// <summary>
        /// This event is called when the up button is pressed and before the value is incremented
        /// It allows me to see if I'm at my internal maximum and cancel the increment if I don't want it to happen
        /// </summary>
        /// <param name="sender"></param>
        ///// <param name="e"></param>       
        void m_numPeriod_UpEvent(object sender, CyUpButtonEventArgs e)
        {
            if (m_rbResolution8.Checked && (m_numPeriod.Value == CyCounterParameters.CONST_2_8))
            {
                e.m_cancel = true;
                return;
            }
            if (m_rbResolution16.Checked && (m_numPeriod.Value == CyCounterParameters.CONST_2_16))
            {
                e.m_cancel = true;
                return;
            }
            if (m_rbResolution24.Checked && (m_numPeriod.Value == CyCounterParameters.CONST_2_24))
            {
                e.m_cancel = true;
                return;
            }
            if (m_rbResolution32.Checked && (m_numPeriod.Value == CyCounterParameters.CONST_2_32))
            {
                e.m_cancel = true;
                return;
            }
        }

        // <summary>
        // This event is called when the down button is pressed and before the value is decremented
        // It allows me to see if I'm at my internal minimum and cancel the increment if I don't want it to happen
        // </summary>
        // <param name="sender"></param>
        //<param name="e"></param>      
        void m_numCompare1_DownEvent(object sender, CyDownButtonEventArgs e)
        {
            if (m_numCompare1.Value == 0)
            {
                e.m_cancel = true;
                return;
            }
        }

        ///// <summary>
        ///// This event is called when the up button is pressed and before the value is incremented
        ///// It allows me to see if I'm at my internal maximum and cancel the increment if I don't want it to happen
        ///// </summary>
        ///// <param name="sender"></param>
        ///// <param name="e"></param>        
        void m_numCompare1_UpEvent(object sender, CyUpButtonEventArgs e)
        {
            if (m_cbClockMode.SelectedIndex == 2 || m_cbClockMode.SelectedIndex == 3)
            {
                if (m_numCompare1.Value == m_numPeriod.Value)
                {
                    e.m_cancel = true;
                    return;
                }
                if (m_rbResolution8.Checked && (m_numCompare1.Value == CyCounterParameters.CONST_2_8))
                {
                    e.m_cancel = true;
                    return;
                }
                if (m_rbResolution16.Checked && (m_numCompare1.Value == CyCounterParameters.CONST_2_16))
                {
                    e.m_cancel = true;
                    return;
                }
                if (m_rbResolution24.Checked && (m_numCompare1.Value == CyCounterParameters.CONST_2_24))
                {
                    e.m_cancel = true;
                    return;
                }
                if (m_rbResolution32.Checked && (m_numCompare1.Value == CyCounterParameters.CONST_2_32))
                {
                    e.m_cancel = true;
                    return;
                }
            }
            else
            {
                if (m_rbResolution8.Checked && (m_numCompare1.Value == CyCounterParameters.CONST_2_8))
                {
                    e.m_cancel = true;
                    return;
                }
                if (m_rbResolution16.Checked && (m_numCompare1.Value == CyCounterParameters.CONST_2_16))
                {
                    e.m_cancel = true;
                    return;
                }
                if (m_rbResolution24.Checked && (m_numCompare1.Value == CyCounterParameters.CONST_2_24))
                {
                    e.m_cancel = true;
                    return;
                }
                if (m_rbResolution32.Checked && (m_numCompare1.Value == CyCounterParameters.CONST_2_32))
                {
                    e.m_cancel = true;
                    return;
                }
            }
        }

        private void m_numCompare1_Validating(object sender, CancelEventArgs e)
        {
            if (m_cbClockMode.SelectedIndex == 2 || m_cbClockMode.SelectedIndex == 3)
            {
                if (m_numCompare1.Value < 0 || m_numCompare1.Value > m_numPeriod.Value)
                {
                    ep_Errors.SetError(m_numCompare1,
                    string.Format("Compare Value must be between 0 and the Period Value of {0}", m_numPeriod.Value));
                    e.Cancel = true;
                }
                else
                {
                    ep_Errors.SetError(m_numCompare1, emptyStr);
                }
            }
            else
            {
                if (m_rbResolution8.Checked && ((m_numCompare1.Value < 0) ||
                   (m_numCompare1.Value > CyCounterParameters.CONST_2_8)))
                {
                    ep_Errors.SetError(m_numCompare1, string.Format("Compare Value must be between 0 and {0}",
                                       CyCounterParameters.CONST_2_8));
                    e.Cancel = true;
                }
                else if (m_rbResolution16.Checked && ((m_numCompare1.Value < 0) ||
                        (m_numCompare1.Value > CyCounterParameters.CONST_2_16)))
                {
                    ep_Errors.SetError(m_numCompare1, string.Format("Compare Value must be between 0 and {0}",
                                      CyCounterParameters.CONST_2_16));
                    e.Cancel = true;
                }
                else if (m_rbResolution24.Checked && ((m_numCompare1.Value < 0) ||
                        (m_numCompare1.Value > CyCounterParameters.CONST_2_24)))
                {
                    ep_Errors.SetError(m_numCompare1, string.Format("Compare Value must be between 0 and {0}",
                                       CyCounterParameters.CONST_2_24));
                    e.Cancel = true;
                }
                else if (m_rbResolution32.Checked && ((m_numCompare1.Value < 0) || (m_numCompare1.Value >
                         CyCounterParameters.CONST_2_32)))
                {
                    ep_Errors.SetError(m_numCompare1, string.Format("Compare Value must be between 0 and {0}",
                                       CyCounterParameters.CONST_2_32));
                    e.Cancel = true;
                }
                else
                    ep_Errors.SetError(m_numCompare1, emptyStr);
            }
        }

        private void CyCounterControl_Load(object sender, EventArgs e)
        {
            if (m_component.DeviceQuery.IsPSoC4)
            {
                m_rbFixedFunction.Visible = false;
                m_rbUDB.Left = m_rbFixedFunction.Left;
                m_rbUDB.Top = m_rbFixedFunction.Top;
                m_rbUDB.Enabled = false;
                m_rbUDB_Click(m_rbUDB, new EventArgs());
            }
        }

        public string GetPeriodError()
        {
            return ep_Errors.GetError(m_numPeriod).Trim();
        }
    }

    /// <summary>
    /// Declaration of the UpButtonEvent must be outside of the class which is CyNumericUpDown
    /// </summary>
    /// <param name="sender"></param>
    /// <param name="e"></param>
    public delegate void UpButtonEvent(object sender, CyUpButtonEventArgs e);

    /// <summary>
    /// Declaration of the DownButtonEvent must be outside of the class which is CyNumericUpDown
    /// </summary>
    /// <param name="sender"></param>
    /// <param name="e"></param>
    public delegate void DownButtonEvent(object sender, CyDownButtonEventArgs e);

    /// <summary>
    /// Custom Event Args for the UpButtonEvent Delegate needs to allow the event to be cancelled before the value 
    /// is changed
    /// </summary>
    public class CyUpButtonEventArgs : EventArgs
    {
        public bool m_cancel;

        public CyUpButtonEventArgs()
        {
            m_cancel = false;
        }
    }
    /// <summary>
    /// Custom Event Args for the DownButtonEvent Delegate needs to allow the event to be cancelled before the value
    /// is changed
    /// </summary>
    public class CyDownButtonEventArgs : EventArgs
    {
        public bool m_cancel;

        public CyDownButtonEventArgs()
        {
            m_cancel = false;
        }
    }

    /// <summary>
    /// Ovverride the base numeric up down so that enter key strokes aren't passed to the parent form.
    /// </summary>
    public class CyNumericUpDown : NumericUpDown
    {

        public event UpButtonEvent UpEvent;
        public event DownButtonEvent DownEvent;

        protected virtual void OnUpEvent(CyUpButtonEventArgs e)
        {
            UpEvent(this, e);
        }

        protected virtual void OnDownEvent(CyDownButtonEventArgs e)
        {
            DownEvent(this, e);
        }

        protected override bool ProcessCmdKey(ref Message msg, Keys keyData)
        {
            if (keyData == Keys.Enter)
            {
                this.ValidateEditText();
                SendKeys.Send("{TAB}");
                return true;
            }
            else
            {
                return base.ProcessCmdKey(ref msg, keyData);
            }
        }

        public override void UpButton()
        {

            CyUpButtonEventArgs e = new CyUpButtonEventArgs();
            OnUpEvent(e);
            if (!e.m_cancel)
                base.UpButton();
        }

        public override void DownButton()
        {
            CyDownButtonEventArgs e = new CyDownButtonEventArgs();
            OnDownEvent(e);
            if (!e.m_cancel)
                base.DownButton();
        }
    }
}
