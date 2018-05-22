/*******************************************************************************
* Copyright 2016-2017, Cypress Semiconductor Corporation. All rights reserved.
* You may use this file only in accordance with the license, terms, conditions, 
* disclaimers, and limitations in the end user license agreement accompanying 
* the software package with which this file was provided.
********************************************************************************/

using System;
using System.Diagnostics;
using System.Text;
using System.Windows.Forms;
using CyDesigner.Extensions.Gde;

namespace SCB_SPI_PDL_v2_0.Controls
{
    public partial class CyDynamicDataControl : UserControl
    {
        CyParameters m_params;

        ErrorProvider m_errorProvider;
        ErrorProvider m_warningProvider;
        ErrorProvider m_noteProvider;

        CyEModeType m_prevMode;
        bool m_prevClockFromTerm;
        uint m_prevDataRateKhz;
        uint m_prevOversample;
        bool m_prevGlitchFilter;

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
            m_prevMode = m_params.Mode;
            m_prevDataRateKhz = m_params.DataRateKhz;
            m_prevClockFromTerm = m_params.ClockFromTerminal;
            m_prevOversample = m_params.OvsFactor;
            m_prevGlitchFilter = m_params.EnableInputGlitchFilter;

            m_params.DesignUpdated += m_params_DesignUpdated;
        }
        #endregion

        #region UI update
        public void UpdateUI(ICyInstQuery_v1 query, ICyTerminalQuery_v1 termQuery)
        {
            bool modeChanged = m_prevMode != m_params.Mode;
            bool clockFromTermChanged = m_prevClockFromTerm != m_params.ClockFromTerminal;
            bool dataRateChanged = m_prevDataRateKhz != m_params.DataRateKhz;

            bool oversampleChanged = (!m_params.ClockFromTerminal && (m_params.Mode == CyEModeType.SPI_MASTER)) ?
                                        (m_prevOversample != m_params.OvsFactor) : false;

            bool glitchFilterChanged = (!m_params.ClockFromTerminal && (m_params.Mode == CyEModeType.SPI_SLAVE)) ?
                                        (m_prevGlitchFilter != m_params.EnableInputGlitchFilter) : false;

            // Update clock true means: display UNKOWN and wait Apply button press.
            // Otherwise read SCB clock frequency and update calculated labels.
            bool clockNeedsUpdate = modeChanged || clockFromTermChanged || dataRateChanged || 
                                    oversampleChanged || glitchFilterChanged;

            UpdateClock(clockNeedsUpdate);
            ToggleSclkMode();
        }

        private void m_params_DesignUpdated(object sender, EventArgs e)
        {
            m_prevMode = m_params.Mode;
            m_prevClockFromTerm = m_params.ClockFromTerminal;
            m_prevDataRateKhz = m_params.DataRateKhz;
            m_prevOversample = m_params.OvsFactor;
            m_prevGlitchFilter = m_params.EnableInputGlitchFilter;

            UpdateClock();
        }

        private void UpdateClock(bool clockNeedsUpdate = false)
        {
            string dataRateStr = Resources.ClockDisplayUnknown;
            
            // Clear all notifications
            ClearNotifications(m_lblActualDataRateValue);

            if (clockNeedsUpdate == false)
            {
                double actualDataRate = m_params.GetActualDataRate();

                // Check valid data rate is returned
                if (actualDataRate > 0)
                {
                    dataRateStr = actualDataRate.ToString();

                    string constMsg = (m_params.Mode == CyEModeType.SPI_MASTER) ?
                    Resources.ActualDataRateNoteMaster : Resources.ActualDataRateNoteSlave;

                    StringBuilder sb = new StringBuilder();

                    // Check actual data rate only when Clock is internal
                    if ((m_params.ClockFromTerminal == false) && 
                        (m_params.DataRateKhz > (actualDataRate + CyParamRanges.EPS)))
                    {
                        sb.Append("1. ").AppendLine(Resources.ActualDataRateLessThanDesired);
                        sb.Append("2. ").AppendLine(constMsg);
                    }
                    else
                    {
                        sb.AppendLine(constMsg);
                    }
                    sb.AppendLine();
                    sb.AppendLine(Resources.ConsultDoc);

                    m_noteProvider.SetError(m_lblActualDataRateValue, sb.ToString());
                }
            }

            // Update Actual Data Rate label
            m_lblActualDataRateValue.Text = dataRateStr;

            // Update apply notification
            m_lblApply.Visible = clockNeedsUpdate;
        }

        void ToggleSclkMode()
        {
            //For  "TI (Start coincides)" and "TI (Start precedes)" must be automatically selected 
            //to "Mode 2 (CPHA = 1, CPOL = 0)" and cannot be changed.

            //For  "National Semiconductor)" must be automatically selected to 
            //"Mode 0 (CPHA = 0, CPOL = 0)" and cannot be changed.
            switch (m_params.SubMode)
            {
                case CyESubModeType.TI_COINCIDES:
                case CyESubModeType.TI_PRECEDES:
                    m_params.SclkMode = CyESCLKModeType.MODE_10;
                    break;
                case CyESubModeType.NS:
                    m_params.SclkMode = CyESCLKModeType.MODE_00;
                    break;
                case CyESubModeType.MOTOROLA:
                    // any SCLK mode is available in this mode
                    break;
                default:
                    Debug.Fail("unhandled enum item.");
                    break;
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
