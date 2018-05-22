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
using System.Diagnostics;

namespace SCB_I2C_PDL_v2_0.Controls
{
    public partial class CyDynamicDataControl : UserControl
    {
        CyParameters m_params;

        ErrorProvider m_errorProvider;
        ErrorProvider m_warningProvider;
        ErrorProvider m_noteProvider;

        CyEModeType m_prevMode;
        ushort m_prevDataRate;
        bool m_prevClockFromTerm;
        bool m_prevManualSclControl;

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
            m_prevMode = m_params.Mode;
            m_prevDataRate = m_params.DataRate;
            m_prevClockFromTerm = m_params.ClockFromTerm;
            m_prevManualSclControl = m_params.ManualSclControl;

            m_params.DesignUpdated += m_params_DesignUpdated;
        }
        #endregion

        #region UI update
        public void UpdateUI()
        {
            bool modeChanged = m_prevMode != m_params.Mode;
            bool dataRateChanged = m_prevDataRate != m_params.DataRate;
            bool clockFromTermChanged = m_prevClockFromTerm != m_params.ClockFromTerm;
            bool sclControlChanged = m_prevManualSclControl != m_params.ManualSclControl;

            bool clockNeedsUpdate = modeChanged || dataRateChanged || sclControlChanged || clockFromTermChanged;
            UpdateClock(clockNeedsUpdate);
        }

        private void m_params_DesignUpdated(object sender, EventArgs e)
        {
            m_prevMode = m_params.Mode;
            m_prevDataRate = m_params.DataRate;
            m_prevClockFromTerm = m_params.ClockFromTerm;
            m_prevManualSclControl = m_params.ManualSclControl;

            UpdateClock();
        }

        private void UpdateClock(bool clockNeedsUpdate = false)
        {
            uint actualDataRate = 0;
            double actualScbClk = 0;

            string dataRateStr = Resources.Unknown;
            string freqStr = Resources.Unknown;
            
            ClearNotifications(m_lblActualDataRateValue);
            ClearNotifications(m_lblScbClockValue);

            if (clockNeedsUpdate == false)
            {
                CyCustErr errClk = m_params.GetScbClock(out actualScbClk);

                // Process if clock is known
                if (errClk.ErrorId != (int)CyParameters.CyEClockErrorID.UNKNOWN_CLK)
                {
                    if (errClk.IsNotOK)
                    {
                        switch (errClk.ErrorId)
                        {
                            case (int)CyParameters.CyEClockErrorID.ERROR_SLAVE_CLK_BELOW_MIN:
                            case (int)CyParameters.CyEClockErrorID.ERROR_SLAVE_CLK_IN_GAP:
                            case (int)CyParameters.CyEClockErrorID.ERROR_SLAVE_CLK_ABOVE_MAX:
                                dataRateStr = Resources.ClockDisplayError;
                                m_errorProvider.SetError(m_lblScbClockValue, errClk.Message);
                                break;

                            case (int)CyParameters.CyEClockErrorID.NOTE_MASTER_CLK_OUT_OF_RANGE:
                            case (int)CyParameters.CyEClockErrorID.NOTE_SLAVE_CLK_SUPPORT_TWO_DR:
                                m_noteProvider.SetError(m_lblScbClockValue, errClk.Message);
                                break;

                            case (int)CyParameters.CyEClockErrorID.UNKNOWN_CLK:
                                // Do nothing: this case is handled above
                                break;

                            default:
                                Debug.Fail("This CyEClockErrorID proccessing is skipped");
                                break;
                        }
                    }
                    
                    // Update scb clock frequency to display
                    freqStr = actualScbClk.ToString();
                }

                // Get oversample
                uint actualOvsFactor = 0;
                if (m_params.Mode != CyEModeType.SLAVE)
                {
                    if (m_params.ManualSclControl)
                    {
                        actualOvsFactor = (uint)(m_params.SclLowPhase + m_params.SclHighPhase);
                    }
                    else
                    {
                        byte lowPhase;
                        byte highPhase;
                        m_params.GetAutoOversamplingLowHigh(out lowPhase, out highPhase);
                        actualOvsFactor = (uint)(lowPhase + highPhase);
                    }
                }

                CyCustErr errDataRate = m_params.GetActualDataRate(actualOvsFactor, out actualDataRate);

                // Do not update if clock is there is clock get error or clock out of range
                if ((errDataRate.ErrorId != (int)CyParameters.CyEDataRateErrorID.UNKNOWN_CLK) &&
                    (String.Compare(dataRateStr, Resources.ClockDisplayError) != 0))
                {
                    // Update data rate to display
                    dataRateStr = actualDataRate.ToString();

                    if (errDataRate.IsNotOK)
                    {
                        switch (errDataRate.ErrorId)
                        { 
                            case (int) CyParameters.CyEDataRateErrorID.ERROR_MASTER_DR_ABOVE_MAX: 
                                m_errorProvider.SetError(m_lblActualDataRateValue, errDataRate.Message);
                                break;

                            case (int) CyParameters.CyEDataRateErrorID.WARNING_SLAVE_DR_NOT_MATCH:
                            case (int) CyParameters.CyEDataRateErrorID.WARNING_MASTER_DR_NOT_MATCH:
                                m_warningProvider.SetError(m_lblActualDataRateValue, errDataRate.Message);
                                break;

                            case (int) CyParameters.CyEDataRateErrorID.NOTE_MASTER_DR_NOT_MATCH:
                                m_noteProvider.SetError(m_lblActualDataRateValue, errDataRate.Message);
                                break;
                                
                            case (int)  CyParameters.CyEDataRateErrorID.UNKNOWN_CLK:
                                // Do nothing: this case is handled above
                                break;

                            default:
                                Debug.Fail("This CyEDataRateErrorID proccessing is skipped");
                                break;
                        }
                    }
                }
            }

            // Update Actual Data Rate  and Clock frequency labels
            m_lblActualDataRateValue.Text = dataRateStr;
            m_lblScbClockValue.Text = freqStr;

            // Show message to press Apply
            m_lblApply.Visible = clockNeedsUpdate;

            // Update SCL low and high phase time (do not show for the slave mode)
            UpdatePhaseTime(actualScbClk, clockNeedsUpdate);
        }

        private void UpdatePhaseTime(double clock, bool displayUnknown = false)
        {
            byte sclLow;
            byte sclHigh;

            if (m_params.ManualSclControl)
            {
                sclLow = m_params.SclLowPhase;
                sclHigh = m_params.SclHighPhase;
            }
            else
            {
                m_params.GetAutoOversamplingLowHigh(out sclLow, out sclHigh);
            }

            m_lblTLowValue.Text = (displayUnknown == false && clock > 0)
                ? (GetSclPhase(clock, sclLow)).ToString()
                : Resources.Unknown;

            m_lblTHighValue.Text = (displayUnknown == false && clock > 0)
                ? (GetSclPhase(clock, sclHigh)).ToString()
                : Resources.Unknown;

            // Do not show for the slave mode
            m_lblTLowText.Visible = (m_params.Mode != CyEModeType.SLAVE);
            m_lblTLowValue.Visible = (m_params.Mode != CyEModeType.SLAVE);
            m_lblTHighText.Visible = (m_params.Mode != CyEModeType.SLAVE);
            m_lblTHighValue.Visible = (m_params.Mode != CyEModeType.SLAVE);
        }

        private static double GetSclPhase(double clock, byte sclPhase)
        {
            return Math.Round(1 / (clock * 1000) * sclPhase * 1000000000);
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
