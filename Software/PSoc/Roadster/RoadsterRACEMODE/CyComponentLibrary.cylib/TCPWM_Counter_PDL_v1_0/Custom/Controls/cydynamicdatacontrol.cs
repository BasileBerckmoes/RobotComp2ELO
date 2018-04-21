/*******************************************************************************
* Copyright 2016, Cypress Semiconductor Corporation. All rights reserved.
* You may use this file only in accordance with the license, terms, conditions, 
* disclaimers, and limitations in the end user license agreement accompanying 
* the software package with which this file was provided.
********************************************************************************/

using System;
using System.Windows.Forms;
using CyDesigner.Extensions.Gde;
using CyDesigner.Extensions.Common;
using TCPWM_Counter_PDL_v1_0.Utils;
using CyDesigner.Toolkit;

namespace TCPWM_Counter_PDL_v1_0.Controls
{
    public partial class CyDynamicDataControl : UserControl
    {
        #region Constructor(s)
        public CyDynamicDataControl()
        {
            InitializeComponent();
        }
        #endregion

        #region UI update
        public void UpdateUI(ICyInstQuery_v1 query, ICyTerminalQuery_v1 termQuery)
        {
            UpdateLabels(query, termQuery);
        }

        public void UpdateClock(ICyInstQuery_v1 query, ICyTerminalQuery_v1 termQuery)
        {
            UpdateLabels(query, termQuery);
        }
        #endregion

        #region Calculated labels
        private void UpdateLabels(ICyInstQuery_v1 query, ICyTerminalQuery_v1 termQuery)
        {
            UpdateCountingClock(query, termQuery);
            UpdatePeriodClock(query, termQuery);
        }

        private void UpdateCountingClock(ICyInstQuery_v1 query, ICyTerminalQuery_v1 termQuery)
        {
            CyEnums.CyClockPrescaler clockPrescaler = CyParameters.GetClockPrescaler(query);
            double clockFreqKHz = CyParameters.GetExternalClockKhz(termQuery);

            if (CyClock.IsFrequencyKnown(clockFreqKHz))
            {
                byte prescaler = CyEnums.ToDisplayValue(clockPrescaler);
                double counterClock = CyMath.GetCounterClock(clockFreqKHz, prescaler);
                counterClock = Math.Round(counterClock, 3);
                m_lblCountingClockValue.Text = counterClock.ToString();
            }
            else
            {
                m_lblCountingClockValue.Text = Resources.UnknownLabel;
            }
        }

        private void UpdatePeriodClock(ICyInstQuery_v1 query, ICyTerminalQuery_v1 termQuery)
        {
            CyCustErr error;
            uint period = CyParameters.GetPeriod(query, out error);
            CyEnums.CyClockPrescaler clockPrescaler = CyParameters.GetClockPrescaler(query);
            double clockFreqKHz = CyParameters.GetExternalClockKhz(termQuery);

            if (CyClock.IsFrequencyKnown(clockFreqKHz) && error.IsOk)
            {
                byte prescaler = CyEnums.ToDisplayValue(clockPrescaler);
                m_lblPeriodClockValue.Text = CyMath.GetPeriodFreq(clockFreqKHz, prescaler, period).ToString();
            }
            else
            {
                m_lblPeriodClockValue.Text = Resources.UnknownLabel;
            }
        }
        #endregion
    }
}
