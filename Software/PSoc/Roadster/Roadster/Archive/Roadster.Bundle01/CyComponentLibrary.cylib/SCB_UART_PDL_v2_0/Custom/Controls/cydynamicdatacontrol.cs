/*******************************************************************************
* Copyright 2016-2017, Cypress Semiconductor Corporation. All rights reserved.
* You may use this file only in accordance with the license, terms, conditions, 
* disclaimers, and limitations in the end user license agreement accompanying 
* the software package with which this file was provided.
********************************************************************************/

using System;
using System.Diagnostics;
using System.Windows.Forms;
using CyDesigner.Extensions.Gde;

namespace SCB_UART_PDL_v2_0.Controls
{
    internal partial class CyDynamicDataControl : UserControl
    {
        CyParameters m_params;

        ErrorProvider m_errorProvider;
        ErrorProvider m_warningProvider;
        ErrorProvider m_noteProvider;

        CyESubModeType m_prevComMode;
        uint m_prevBaudRate;
        ushort m_prevOversampling;
        bool m_prevClockFromTerm;

        #region Constructor(s)
        public CyDynamicDataControl(CyParameters parameters)
        {
            InitializeComponent();
            Dock = DockStyle.Fill;
            AutoScroll = true;

            m_errorProvider = new ErrorProvider() { BlinkStyle = ErrorBlinkStyle.NeverBlink };
            m_warningProvider = new ErrorProvider() { BlinkStyle = ErrorBlinkStyle.NeverBlink, Icon = Resources.WarningIco };
            m_noteProvider = new ErrorProvider() { BlinkStyle = ErrorBlinkStyle.NeverBlink, Icon = Resources.InfoIco };

            m_params = parameters;
            m_prevComMode = m_params.ComMode;
            m_prevBaudRate = m_params.BaudRate;
            m_prevOversampling = m_params.OvsFactor;
            m_prevClockFromTerm = m_params.ClockFromTerminal;

            m_params.DesignUpdated += m_params_DesignUpdated;
        }
        #endregion

        #region UI update
        public void UpdateUI(ICyInstQuery_v1 query, ICyTerminalQuery_v1 termQuery)
        {
            bool comModeChanged = m_prevComMode != m_params.ComMode;
            bool baudRateChanged = m_prevBaudRate != m_params.BaudRate;
            bool oversamplingChanged = m_prevOversampling != m_params.OvsFactor;
            bool clockFromTermChanged = m_prevClockFromTerm != m_params.ClockFromTerminal;

            bool clockNeedsUpdate = comModeChanged || baudRateChanged || oversamplingChanged || clockFromTermChanged;
            
            UpdateClock(clockNeedsUpdate);

            ToggleDirection();
            ToggleOvsFactor();
            ToggleParityType();
            ToggleStopBit();
        }

        private void m_params_DesignUpdated(object sender, EventArgs e)
        {
            m_prevComMode = m_params.ComMode;
            m_prevBaudRate = m_params.BaudRate;
            m_prevOversampling = m_params.OvsFactor;
            m_prevClockFromTerm = m_params.ClockFromTerminal;

            UpdateClock();
        }

        private void UpdateClock(bool clockNeedsUpdate = false)
        {
            const double MAX_RECOMMENDED_TOLERANCE_PCT = 2.5;
            string dataRateStr = Resources.ClockDisplayUnknown;

            ClearNotifications(m_lblActualBaudRateValue);

            double actualDataRate = m_params.GetActualDataRate() * 1000;
            if (actualDataRate > 0 && clockNeedsUpdate == false)
            {
                dataRateStr = actualDataRate.ToString();

                if (m_params.ClockFromTerminal == false)
                {
                    CyClockData sclkData = m_params.ClockFromTerminal
                        ? CyParameters.GetExternalClockData(m_params.TermQuery)
                        : CyParameters.GetInternalClockData(m_params.TermQuery);

                    if (sclkData != null)
                    {
                        double minusAccuracyPct = sclkData.MinusAccuracyPct;
                        double plusAccuracyPct = sclkData.PlusAccuracyPct;

                        double minusDelta = ((MAX_RECOMMENDED_TOLERANCE_PCT - minusAccuracyPct) / 100);
                        double plusDelta = ((MAX_RECOMMENDED_TOLERANCE_PCT - plusAccuracyPct) / 100);

                        if (actualDataRate < (m_params.BaudRate - m_params.BaudRate * minusDelta) ||
                            actualDataRate > (m_params.BaudRate + m_params.BaudRate * plusDelta))
                        {
                            m_noteProvider.SetError(m_lblActualBaudRateValue, Resources.ToleranceNote);
                        }
                    }
                }
            }

            // Update actual data rate label
            m_lblActualBaudRateValue.Text = dataRateStr;
            m_lblApply.Visible = clockNeedsUpdate;
        }

        private void ToggleDirection()
        {
            if (m_params.ComMode == CyESubModeType.SMART_CARD)
            {
                m_params.Direction = CyEDirectionType.TX_RX;
            }
        }

        private void ToggleOvsFactor()
        {
            if ((m_params.ComMode == CyESubModeType.IRDA) && !m_params.ClockFromTerminal)
            {
                if (m_params.LowPowerReceive)
                {
                    if (CyParamRanges.IRDA_DATA_RATES_LIST.ContainsKey(m_params.BaudRate))
                    {
                        m_params.OvsFactor = CyParamRanges.IRDA_DATA_RATES_LIST[m_params.BaudRate];
                    }
                }
                else
                {
                    m_params.OvsFactor = CyParamRanges.OVS_FACTOR_MAX;
                }
            }
        }

        private void ToggleParityType()
        {
            switch (m_params.ComMode)
            {
                case CyESubModeType.STANDARD:
                    if (m_params.DataWidth == CyEDataWidthType.NINE)
                    {
                        m_params.ParityType = CyEParityType.NONE;
                    }
                    break;
                case CyESubModeType.SMART_CARD:
                    m_params.ParityType = CyEParityType.EVEN;
                    break;
                case CyESubModeType.IRDA:
                    m_params.ParityType = CyEParityType.NONE;
                    break;
                default:
                    Debug.Fail("unhandled enum item.");
                    break;
            }
        }

        private void ToggleStopBit()
        {
            if (m_params.ComMode == CyESubModeType.SMART_CARD)
            {
                m_params.StopBits = CyEStopBitsType.TWO_BITS;
            }
        }
        #endregion

        #region Error/Warning/Note provider methods
        /// <summary>
        /// Clears error, warning and note notifications that are being displayed next to the control.
        /// </summary>
        /// <param name="control">Control which notifications should be cleared.</param>
        protected void ClearNotifications(Control control)
        {
            m_errorProvider.SetError(control, String.Empty);
            m_warningProvider.SetError(control, String.Empty);
            m_noteProvider.SetError(control, String.Empty);
        }
        #endregion
    }
}
