/*******************************************************************************
* Copyright 2013, Cypress Semiconductor Corporation.  All rights reserved.
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

namespace LED_Driver_v1_10
{
    public partial class CyGeneralTab : UserControl, ICyParamEditingControl
    {
        protected CyParameters m_params = null;
        protected ErrorProvider m_errorProvider = null;

        /// <summary>
        /// This property returns the tab name that will be associated with parameters in expression view.
        /// </summary>
        public virtual string TabName
        {
            get { return "Basic"; }
        }

        #region Constructor(s)
        public CyGeneralTab()
        {
            InitializeComponent();

            m_numRefreshRate.Maximum = decimal.MaxValue;

            #region Add comboboxes' items
            m_cbNumSegments.Items.Clear();
            for (byte i = CyParamRanges.MIN_SEGMENTS; i <= CyParamRanges.MAX_SEGMENTS; i++)
            {
                m_cbNumSegments.Items.Add(i);
            }

            m_cbNumCommons.Items.Clear();
            for (byte i = CyParamRanges.MIN_COMMONS; i <= CyParamRanges.MAX_COMMONS; i++)
            {
                m_cbNumCommons.Items.Add(i);
            }
            #endregion

            m_cbNumSegments.SelectedIndexChanged += new EventHandler(m_cbNumSelectedIndexChanged);
            m_cbNumCommons.SelectedIndexChanged += new EventHandler(m_cbNumSelectedIndexChanged);

            m_rbCommonDriveLow.CheckedChanged += new EventHandler(m_rbCheckedChanged);
            m_rbCommonDriveHigh.CheckedChanged += new EventHandler(m_rbCheckedChanged);
            m_rbSeqmentDriveLow.CheckedChanged += new EventHandler(m_rbCheckedChanged);
            m_rbSeqmentDriveHigh.CheckedChanged += new EventHandler(m_rbCheckedChanged);
            m_rbInternalClock.CheckedChanged += new EventHandler(m_rbCheckedChanged);
            m_rbExternalClock.CheckedChanged += new EventHandler(m_rbCheckedChanged);
            m_rbDisableBrightnessCtl.CheckedChanged += new EventHandler(m_rbCheckedChanged);
            m_rbEnableBrightnessCtl.CheckedChanged += new EventHandler(m_rbCheckedChanged);

            m_numRefreshRate.TextChanged += new EventHandler(m_numTextChanged);
        }

        public CyGeneralTab(CyParameters parameters) : this()
        {
            m_params = parameters;

            m_errorProvider = new ErrorProvider();
            m_errorProvider.BlinkStyle = ErrorBlinkStyle.NeverBlink;

            this.Dock = DockStyle.Fill;
            this.AutoScroll = true;
        }
        #endregion

        #region ICyParamEditingControl members
        public Control DisplayControl
        {
            get { return this; }
        }

        public IEnumerable<CyCustErr> GetErrors()
        {
            string errorMessage = string.Empty;

            if (m_errorProvider != null)
            {
                // Check controls for errors
                foreach (Control control in this.Controls)
                {
                    errorMessage = m_errorProvider.GetError(control);
                    if (string.IsNullOrEmpty(errorMessage) == false)
                        yield return new CyCustErr(errorMessage);

                    // Check controls inside groupbox
                    foreach (Control internalControl in control.Controls)
                    {
                        errorMessage = m_errorProvider.GetError(internalControl);
                        if (string.IsNullOrEmpty(errorMessage) == false)
                            yield return new CyCustErr(errorMessage);
                    }
                }
            }

            foreach (string paramName in m_params.m_instQuery.GetParamNames())
            {
                CyCompDevParam param = m_params.m_instQuery.GetCommittedParam(paramName);
                if (param.TabName.Equals(TabName))
                {
                    if (param.ErrorCount > 0)
                    {
                        foreach (string errMsg in param.Errors)
                        {
                            yield return new CyCustErr(errMsg);
                        }
                    }
                }
            }
        }
        #endregion

        public void UpdateUI()
        {
            m_cbNumSegments.SelectedItem = m_params.NumberOfSegments;
            m_cbNumCommons.SelectedItem = m_params.NumberOfCommons;

            switch (m_params.CommonDriveMode)
            {
                case CyEDriveMode.ActiveLow:
                    m_rbCommonDriveLow.Checked = true;
                    break;
                case CyEDriveMode.ActiveHigh:
                    m_rbCommonDriveHigh.Checked = true;
                    break;
            }

            switch (m_params.SegmentDriveMode)
            {
                case CyEDriveMode.ActiveLow:
                    m_rbSeqmentDriveLow.Checked = true;
                    break;
                case CyEDriveMode.ActiveHigh:
                    m_rbSeqmentDriveHigh.Checked = true;
                    break;
            }

            switch (m_params.ClockSource)
            {
                case CyEClockSource.Internal:
                    m_rbInternalClock.Checked = true;
                    break;
                case CyEClockSource.External:
                    m_rbExternalClock.Checked = true;
                    break;
            }

            if (m_params.BrightnessEnabled)
            {
                m_rbEnableBrightnessCtl.Checked = true;
            }
            else
            {
                m_rbDisableBrightnessCtl.Checked = true;
            }

            m_numRefreshRate.Text = m_params.DisplayRefreshRate.ToString();

            UpdateRefreshRate();
        }

        private void UpdateRefreshRate()
        {
            m_numRefreshRate.Enabled = (m_params.ClockSource == CyEClockSource.Internal);

            UInt32 actualRefreshRate = m_params.CalculatedRefreshRate;

            if (CyParameters.IsFrequencyKnown(actualRefreshRate) && (m_params.ClockNeedsUpdate == false))
            {
                m_lblActualRefreshRate.Text = string.Format(Resources.ActualRefreshRateTextFormat,
                    actualRefreshRate, CyParameters.UNITS_HZ);

                if (m_params.ClockSource == CyEClockSource.Internal)
                {
                    m_params.LatestDesiredClkFreq = m_params.ConvertRefreshRateToFrequency(m_params.DisplayRefreshRate);
                }

                // Compare actual refresh rate with bus clock
                if (m_params.CheckFrequencyVsBusClock(actualRefreshRate) == false)
                {
                    warningProvider.SetError(m_lblActualRefreshRate, String.Format(Resources.BusClockCompareError,
                          m_params.GetMaxFreqComparedBusClk()));
                }
                else
                {
                    warningProvider.SetError(m_lblActualRefreshRate, "");
                }
            }
            else
            {
                m_lblActualRefreshRate.Text = string.Format(Resources.ActualRefreshRateTextFormat,
                    CyParameters.UNKNOWN_FREQUENCY_STR, string.Empty);

                warningProvider.SetError(m_lblActualRefreshRate, "");
            }
        }

        public void UpdateRefreshRate(ICyInstQuery_v1 query, ICyTerminalQuery_v1 termQuery)
        {
            m_params.ClockNeedsUpdate = false;
            UpdateRefreshRate();
        }

        private void UpdateRefreshRateErrProvider(double? value)
        {
            if ((value == null) || (value + CyParamRanges.EPS < CyParamRanges.MIN_REFRESH_RATE)) 
            {
                m_errorProvider.SetError(m_numRefreshRate,  Resources.DisplayRefreshRateValueError);
            }
            else
            {
                m_errorProvider.SetError(m_numRefreshRate, string.Empty);
            }
        }

        #region Event handler(s)
        void m_cbNumSelectedIndexChanged(object sender, EventArgs e)
        {
            if (m_params.GlobalEditMode)
            {
                if (sender == m_cbNumSegments)
                {
                    m_params.NumberOfSegments = (byte)m_cbNumSegments.SelectedItem;
                }
                else if (sender == m_cbNumCommons)
                {
                    m_params.NumberOfCommons = (byte)m_cbNumCommons.SelectedItem;
                    
                    m_params.ClockNeedsUpdate = true;
                    UpdateRefreshRate();
                }
            }
        }

        void m_rbCheckedChanged(object sender, EventArgs e)
        {
            if ((sender as RadioButton).Checked == false)
            {
                return;
            }

            if (m_params.GlobalEditMode)
            {
                if ((sender == m_rbCommonDriveLow) || (sender == m_rbCommonDriveHigh))
                {
                    m_params.CommonDriveMode = m_rbCommonDriveHigh.Checked ? CyEDriveMode.ActiveHigh :
                        CyEDriveMode.ActiveLow;
                }
                else if ((sender == m_rbSeqmentDriveLow) || (sender == m_rbSeqmentDriveHigh))
                {
                    m_params.SegmentDriveMode = (m_rbSeqmentDriveHigh.Checked ? CyEDriveMode.ActiveHigh :
                        CyEDriveMode.ActiveLow);
                }
                else if ((sender == m_rbInternalClock) || (sender == m_rbExternalClock))
                {
                    m_params.ClockSource = m_rbInternalClock.Checked ? CyEClockSource.Internal :
                        CyEClockSource.External;
                    UpdateRefreshRate();
                }
                else if ((sender == m_rbDisableBrightnessCtl) || (sender == m_rbEnableBrightnessCtl))
                {
                    m_params.BrightnessEnabled = m_rbEnableBrightnessCtl.Checked;
                    m_params.ClockNeedsUpdate = true;
                    UpdateRefreshRate();
                }
            }
        }

        void m_numTextChanged(object sender, EventArgs e)
        {
            if (m_params.GlobalEditMode)
            {
                if (sender == m_numRefreshRate)
                {
                    UInt32 value;
                    bool parsed = UInt32.TryParse(m_numRefreshRate.Text, out value);

                    if (parsed == true)
                    {
                        m_params.DisplayRefreshRate = value;

                        m_params.ClockNeedsUpdate = true;
                        UpdateRefreshRate();

                        UpdateRefreshRateErrProvider((double)value);
                    }
                    else
                    {
                        UpdateRefreshRateErrProvider(null);
                    }
                }
            }
        }
        #endregion
    }
}
