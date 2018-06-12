/*******************************************************************************
* Copyright 2008-2014, Cypress Semiconductor Corporation.  All rights reserved.
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


namespace FanController_v4_0
{
    public partial class CyBasicTab : CyEditingWrapperControl
    {
        /// <summary>
        /// TabName property of parameters in symbol that are edited on this tab
        /// </summary>
        public override string TabName
        {
            get { return "Basic"; }
        }

        public CyBasicTab(CyParameters param)
            : base(param)
        {
            InitializeComponent();

            // Fill in the percent values in the tolerance drop down
            for (int i = CyParamConst.MIN_TOLERANCE_PERCENT; i <= CyParamConst.MAX_TOLERANCE_PERCENT; i++)
            {
                m_cbFanTolerance.Items.Add(i.ToString() + "%");
            }
            m_nudControlLoopPeriod.Maximum = CyParamConst.MAX_CONTROL_LOOP_PERIOD;

            UpdateFormFromParams();

            m_nudControlLoopPeriod.TextChanged += m_nudControlLoopPeriod_TextChanged;
        }
                
        #region Form Updating Routines
        public void UpdateFormFromParams()
        {
            if (m_prms == null) return;

            // Fan Mode radio buttons
            if (m_prms.GetFanMode() == CyFanModeDisplayType.MANUAL)
            {
                m_rbManual.Checked = true;
                m_rbFirmware.Checked = true;
            }
            else
            {
                m_rbAutomatic.Checked = true;
                if (m_prms.GetFanMode() == CyFanModeDisplayType.AUTO_FIRMWARE)
                {
                    m_rbFirmware.Checked = true;
                }
                else
                    m_rbHardware.Checked = true;
            }

            // Alert Enable checkboxes
            if ((m_prms.AlertEnable & CyParamConst.ALERT_FAN_STALL) != 0)
                m_chbAltFanStall.Checked = true;
            if ((m_prms.AlertEnable & CyParamConst.ALERT_SPEED_FAIL) != 0)
                m_chbAltSpeedFailure.Checked = true;

            m_nudControlLoopPeriod.Value = Math.Min(m_prms.ControlLoopPeriod, m_nudControlLoopPeriod.Maximum);

            int val = m_prms.FanTolerance - 1;
            if (val >= 0 && val < m_cbFanTolerance.Items.Count)
                m_cbFanTolerance.SelectedIndex = val;

            // Acoustic Noise Reduction Checkbox 
            if (m_prms.AcousticNoiseReduction != 0)
                m_chbANR.Checked = true;
            else
                m_chbANR.Checked = false;

            m_chbExternalClock.Checked = m_prms.ExternalClock;

            m_chbDisplayBus.Checked = m_prms.Connection == CyConnectinType.BUSSED;
        
            UpdateControlEnableState();
        }

        #endregion

        #region Event handlers
        /// <summary>
        /// This event handler is assigned to four radio buttons: rbManual, rbAutomatic, rbFirmware, rbHardware
        /// </summary>
        private void rbMode_CheckedChanged(object sender, EventArgs e)
        {
            if (((RadioButton)sender).Checked == false)
                return;

            CyFanModeDisplayType fanMode = CyFanModeDisplayType.MANUAL;
            if (m_rbAutomatic.Checked)
            {
                if (m_rbFirmware.Checked)
                    fanMode = CyFanModeDisplayType.AUTO_FIRMWARE;
                else if (m_rbHardware.Checked)
                    fanMode = CyFanModeDisplayType.AUTO_HARDWARE;
            }
            else
            {
                if (m_rbHardware.Checked)
                    m_rbFirmware.Checked = true;
            }
            m_prms.SetFanMode(fanMode);

            // chbAltSpeedFailure checkbox is always disabled in Manual mode
            if (fanMode == CyFanModeDisplayType.MANUAL)
            {
                m_chbAltSpeedFailure.Checked = false;
            }

            // chbANR checkbox is always disabled in Firmware mode
            if (fanMode == CyFanModeDisplayType.AUTO_FIRMWARE)
            {
                m_chbANR.Checked = false;
            }

            UpdateControlEnableState();
            // Validate nudControlLoopPeriod
            m_nudControlLoopPeriod_TextChanged(m_nudControlLoopPeriod, EventArgs.Empty);

            // Update dependent settings on other tab
            m_prms.m_fansTab.UpdateBasicTabRelatedFields();
            m_prms.UpdateTabVisibility();
        }

        /// <summary>
        /// This event handler is assigned to two checkboxes: chbAltFanStall and chbAltSpeedFailure
        /// </summary>
        private void chbAlerts_CheckedChanged(object sender, EventArgs e)
        {
            byte mask = (sender == m_chbAltFanStall) ? CyParamConst.ALERT_FAN_STALL : CyParamConst.ALERT_SPEED_FAIL;
            bool turnBitsOn = (((CheckBox)sender).Checked == true);
            m_prms.AlertEnable = CyAuxFunctions.SetBits(m_prms.AlertEnable, mask, turnBitsOn);
        }

        private void m_chbANR_CheckedChanged(object sender, EventArgs e)
        {
            m_prms.AcousticNoiseReduction = Convert.ToByte(m_chbANR.Checked);
        }

        private void m_cbFanTolerance_SelectedIndexChanged(object sender, EventArgs e)
        {
            m_prms.FanTolerance = (byte)(m_cbFanTolerance.SelectedIndex + 1);
        }

        private void m_chbExternalClock_CheckedChanged(object sender, EventArgs e)
        {
            m_prms.ExternalClock = m_chbExternalClock.Checked;
            m_prms.m_fansTab.UpdateBasicTabRelatedFields();
        }

        private void m_chbDisplayBus_CheckedChanged(object sender, EventArgs e)
        {
            m_prms.Connection = m_chbDisplayBus.Checked ? CyConnectinType.BUSSED : CyConnectinType.WIRED;
        }

        void m_nudControlLoopPeriod_TextChanged(object sender, EventArgs e)
        {
            decimal? nudValue = CyAuxFunctions.ValidateNumUpDown(m_nudControlLoopPeriod, m_errorProvider);
            if (nudValue.HasValue)
            {
                m_prms.ControlLoopPeriod = nudValue.Value;
                ValidateControlLoopPeriodValue();
            }
        }
        #endregion

        #region Private functions
        /// <summary>
        /// Enables or disables controls depending on the selected fan mode and current device
        /// </summary>
        private void UpdateControlEnableState()
        {
            bool isFanModeAutomatic = (m_prms.GetFanMode() != CyFanModeDisplayType.MANUAL);
            bool isFanModeHardware = (m_prms.GetFanMode() == CyFanModeDisplayType.AUTO_HARDWARE);
            bool isFanModeFirmware = (m_prms.GetFanMode() == CyFanModeDisplayType.AUTO_FIRMWARE);

            m_pnlFanMethodAuto.Enabled = isFanModeAutomatic;
            m_pnlAutoSettings.Enabled = isFanModeAutomatic;
            m_chbAltSpeedFailure.Enabled = isFanModeAutomatic;
            m_cbFanTolerance.Enabled = !isFanModeFirmware;
            m_lblTolerance.Enabled = !isFanModeFirmware;
            m_chbANR.Enabled = !isFanModeFirmware;

            // Apply PSoC4 limitations
            if (m_prms.IsPSoC4)
            {
                if (isFanModeHardware == false)
                {
                    m_rbHardware.Enabled = false;
                    m_errorProvider.SetError(m_rbHardware, String.Empty);
                }
                else
                {
                    m_errorProvider.SetError(m_rbHardware, Resources.MsgHardwareModePSoC4);
                }
            }
        }

        private void ValidateControlLoopPeriodValue()
        {
            string errorMsg = String.Empty;
            if ((m_prms.GetFanMode() == CyFanModeDisplayType.AUTO_FIRMWARE) &&
                (m_prms.ControlLoopPeriod < CyParamConst.EPS))
            {
                errorMsg = Resources.ErrorControlLoopPeriodFW;
            }
            m_errorProvider.SetError(m_nudControlLoopPeriod, errorMsg);
        }
        #endregion Private functions 
    }
}

