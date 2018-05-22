/*******************************************************************************
* Copyright 2016-2017, Cypress Semiconductor Corporation. All rights reserved.
* You may use this file only in accordance with the license, terms, conditions, 
* disclaimers, and limitations in the end user license agreement accompanying 
* the software package with which this file was provided.
********************************************************************************/

using System;
using System.Windows.Forms;
using CyDesigner.Toolkit;
using CyDesigner.Extensions.Gde;
using CyDesigner.Extensions.Common;
using TCPWM_PWM_PDL_v1_0.Utils;

namespace TCPWM_PWM_PDL_v1_0.Controls
{
    public partial class CyDynamicDataControl : UserControl
    {
        private const string NO_VALUE = "-";

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

            if (CyParameters.GetPeriodSwap(query) == false)
            {
                m_lblPeriod1Value.Text = NO_VALUE;
            }

            if (CyParameters.GetCompareSwap(query) == false)
            {
                m_lblDutyCycle1Percent.Text = NO_VALUE;
            }
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
            UpdateDutyCycle(query);
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
            uint period0 = CyParameters.GetPeriod0(query, out error);
            uint period1 = CyParameters.GetPeriod1(query, out error);
            CyEnums.CyClockPrescaler clockPrescaler = CyParameters.GetClockPrescaler(query);
            double clockFreqKhz = CyParameters.GetExternalClockKhz(termQuery);

            if (CyClock.IsFrequencyKnown(clockFreqKhz))
            {
                byte prescaler = CyEnums.ToDisplayValue(clockPrescaler);
                m_lblPeriod0Value.Text = CyMath.GetPeriodFreq(clockFreqKhz, prescaler, period0).ToString();
                m_lblPeriod1Value.Text = CyMath.GetPeriodFreq(clockFreqKhz, prescaler, period1).ToString();
            }
            else
            {
                m_lblPeriod0Value.Text = Resources.UnknownLabel;
                m_lblPeriod1Value.Text = Resources.UnknownLabel;
            }
        }

        private void UpdateDutyCycle(ICyInstQuery_v1 query)
        {
            CyCustErr period0Error;
            CyCustErr periodError;
            CyCustErr compare0Error;
            CyCustErr compareError;
            CyEnums.CyMode pwmMode = CyParameters.GetMode(query);
            CyEnums.CyAlignment alignment = CyParameters.GetAlignment(query);
            uint period0 = CyParameters.GetPeriod0(query, out period0Error);
            uint period1 = CyParameters.GetPeriod1(query, out periodError);
            bool periodSwap = CyParameters.GetPeriodSwap(query);
            uint period = periodSwap ? period1 : period0; // Actual period 1
            if (periodSwap == false)
                periodError = period0Error; // Actual period 1 error
            uint compare0 = CyParameters.GetCompare0(query, out compare0Error);
            uint compare1 = CyParameters.GetCompare1(query, out compareError);
            bool compareSwap = CyParameters.GetCompareSwap(query);
            uint compare = compareSwap ? compare1 : compare0; // Actual compare 1
            if (compareSwap == false)
                compareError = compare0Error; // Actual compare 1 error

            if (alignment == CyEnums.CyAlignment.LEFT || alignment == CyEnums.CyAlignment.RIGHT ||
                alignment == CyEnums.CyAlignment.CENTER)
            {
                double dutyCycle0 = CyMath.GetDutyCyclePercentage(alignment, period0, compare0);
                double dutyCycle1 = CyMath.GetDutyCyclePercentage(alignment, period, compare);

                m_lblDutyCycle0Percent.Text = period0Error.IsOk && compare0Error.IsOk
                    ? String.Format("{0}%", dutyCycle0)
                    : NO_VALUE;
                m_lblDutyCycle1Percent.Text = periodError.IsOk && compareError.IsOk
                    ? String.Format("{0}%", dutyCycle1)
                    : NO_VALUE;
            }
            else // Assymetric
            {
                double dutyCycle0 = CyMath.GetDutyCyclePercentage(alignment, period0 * 2, compare0 + compare);
                double dutyCycle1 = CyMath.GetDutyCyclePercentage(alignment, period * 2, compare0 + compare);

                m_lblDutyCycle0Percent.Text = period0Error.IsOk && compare0Error.IsOk && compareError.IsOk
                    ? String.Format("{0}%", dutyCycle0)
                    : NO_VALUE;
                m_lblDutyCycle1Percent.Text = periodError.IsOk && compare0Error.IsOk && compareError.IsOk
                    ? String.Format("{0}%", dutyCycle1)
                    : NO_VALUE;
            }

            // Update labels visibility: Hide if Mode = PseudoRandom
            m_lblDutyCycle0Percent.Visible = pwmMode != CyEnums.CyMode.MODE_PSEUDORANDOM;
            m_lblDutyCycle1Percent.Visible = pwmMode != CyEnums.CyMode.MODE_PSEUDORANDOM;
            m_lblDutyCycle0.Visible = pwmMode != CyEnums.CyMode.MODE_PSEUDORANDOM;
            m_lblDutyCycle1.Visible = pwmMode != CyEnums.CyMode.MODE_PSEUDORANDOM;
        }
        #endregion
    }
}
