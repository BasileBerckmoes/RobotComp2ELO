/*******************************************************************************
* Copyright 2016-2017, Cypress Semiconductor Corporation. All rights reserved.
* You may use this file only in accordance with the license, terms, conditions, 
* disclaimers, and limitations in the end user license agreement accompanying 
* the software package with which this file was provided.
********************************************************************************/

using System;
using System.Windows.Forms;
using CyDesigner.Extensions.Gde;
using CyDesigner.Extensions.Common;

namespace SCB_EZI2C_PDL_v2_0.Controls
{
    public partial class CyDynamicDataControl : UserControl
    {
        CyParameters m_params;

        ErrorProvider m_errorProvider;
        ErrorProvider m_warningProvider;
        ErrorProvider m_noteProvider;

        ushort m_prevDataRate;
        bool m_prevClockFromTerm;

        #region Constructor(s)
        public CyDynamicDataControl(CyParameters parameters)
        {
            InitializeComponent();

            AutoScroll = true;
            Dock = DockStyle.Fill;
            BorderStyle = BorderStyle.FixedSingle;

            m_errorProvider = new ErrorProvider() { BlinkStyle = ErrorBlinkStyle.NeverBlink };
            m_warningProvider = new ErrorProvider() { BlinkStyle = ErrorBlinkStyle.NeverBlink, Icon = Resources.WarningIco };
            m_noteProvider = new ErrorProvider() { BlinkStyle = ErrorBlinkStyle.NeverBlink, Icon = Resources.InformationIconIco };

            m_params = parameters;
            m_prevDataRate = m_params.DataRate;
            m_prevClockFromTerm = m_params.ClockFromTerm;

            m_params.DesignUpdated += m_params_DesignUpdated;
        }
        #endregion

        #region UI update
        public void UpdateUI()
        {
            bool dataRateChanged = (m_prevDataRate != m_params.DataRate);
            bool clockFromTermChanged = (m_prevClockFromTerm != m_params.ClockFromTerm);

            bool clockNeedsUpdate = (dataRateChanged || clockFromTermChanged);

            UpdateClock(clockNeedsUpdate);
        }

        private void m_params_DesignUpdated(object sender, EventArgs e)
        {
            m_prevDataRate = m_params.DataRate;
            m_prevClockFromTerm = m_params.ClockFromTerm;

            UpdateClock();
        }

        private void UpdateClock(bool clockNeedsUpdate = false)
        {
            string dataRateStr = Resources.Unknown;
            string freqStr = Resources.Unknown;

            ClearNotifications(m_lblActualDataRateValue);
            ClearNotifications(m_lblScbClockValue);

            if (clockNeedsUpdate == false)
            {
                uint actualDataRate;

                CyCustErr err = m_params.GetActualDataRate(out actualDataRate);

                // Process if clock is known
                if (err.ErrorId != (int) CyParameters.CyEClockErrorID.UNKNOWN_CLK)
                {
                    double scbClk = m_params.GetClockKhz();

                    if (err.IsNotOK)
                    {
                        dataRateStr = Resources.ClockDisplayError;
                        m_errorProvider.SetError(m_lblScbClockValue, err.Message);
                    }
                    else
                    {
                        // Add note that clock works for two ranges
                        if (scbClk > (CyRanges.SLAVE_FSCB_MIN_400KBPS - CyRanges.EPS) &&
                            scbClk < (CyRanges.SLAVE_FSCB_MAX_100KBPS + CyRanges.EPS))
                        {
                            m_noteProvider.SetError(m_lblScbClockValue, Resources.ClockSupportsBothDataRates);
                        }

                        // Add warning that actual data rate is less than desired
                        if ((actualDataRate < m_params.DataRate) && (m_params.ClockFromTerm == false))
                        {
                            m_warningProvider.SetError(m_lblActualDataRateValue, Resources.DataRateWarning);
                        }

                        // Update data rate to display
                        dataRateStr = actualDataRate.ToString();
                    }

                    // Update clock frequency to display
                    freqStr = Math.Round(scbClk, 3).ToString();
                }
            }

            // Update labels: Data Rate and SCB clock frequency
            m_lblActualDataRateValue.Text = dataRateStr;
            m_lblScbClockValue.Text = freqStr;

            // Update apply notification
            m_lblApply.Visible = clockNeedsUpdate;

        }
        #endregion

        #region Error/Warning/Note provider methods
        /// <summary>
        /// Clears error, warning and note notifications that are displayed next to the specific control.
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
