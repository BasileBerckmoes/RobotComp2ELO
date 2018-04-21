/*******************************************************************************
* Copyright 2013-2016, Cypress Semiconductor Corporation.  All rights reserved.
* You may use this file only in accordance with the license, terms, conditions, 
* disclaimers, and limitations in the end user license agreement accompanying 
* the software package with which this file was provided. 
********************************************************************************/

using System;
using System.Collections.Generic;
using System.Windows.Forms;
using CyDesigner.Extensions.Common;
using CyDesigner.Extensions.Gde;

namespace OpAmp_P4_v1_20
{
    public partial class CyConfigureTab : UserControl, ICyParamEditingControl
    {
        private readonly CyImage m_symbol;

        public string TabName
        {
            get { return "Configure"; }
        }

        private readonly CyParameters m_params;

        #region Constructor(s)
        public CyConfigureTab(CyParameters parameters)
        {
            m_params = parameters;
            InitializeComponent();

            this.Dock = DockStyle.Fill;

            rbModeOpamp.CheckedChanged += rb_CheckedChanged;
            rbModeFollower.CheckedChanged += rb_CheckedChanged;
            rbOutputInternal.CheckedChanged += rb_CheckedChanged;
            rbOutputToPin.CheckedChanged += rb_CheckedChanged;
            rbSpeedSlow.CheckedChanged += rb_CheckedChanged;
            rbSpeedMedium.CheckedChanged += rb_CheckedChanged;
            rbSpeedHigh.CheckedChanged += rb_CheckedChanged;
            m_rbHighSpeed.CheckedChanged += rb_CheckedChanged;
            m_rbBalanced.CheckedChanged += rb_CheckedChanged;
            m_rbHighStability.CheckedChanged += rb_CheckedChanged;
            rb_DeepSleepDisabled.CheckedChanged += rb_CheckedChanged;
            rb_DeepSleepEnabled.CheckedChanged += rb_CheckedChanged;

            m_symbol = new CyImage();
            UpdateSymbolImage();
        }
        #endregion

        #region ICyParamEditingControl Members
        public Control DisplayControl
        {
            get { return this; }
        }

        public IEnumerable<CyCustErr> GetErrors()
        {
            List<CyCustErr> errs = new List<CyCustErr>();
            errs = GetControlErrors(this.Controls);

            foreach (string paramName in m_params.InstQuery.GetParamNames())
            {
                CyCompDevParam param = m_params.InstQuery.GetCommittedParam(paramName);
                if (param.TabName.Equals(TabName))
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

        /// <summary>
        /// Gets a list of errors found on the control.
        /// </summary>
        protected List<CyCustErr> GetControlErrors(ControlCollection controls)
        {
            string errorMessage = String.Empty;
            List<CyCustErr> errs = new List<CyCustErr>();
            foreach (Control control in controls)
            {
                if (control.Enabled)
                {
                    errorMessage = errorProvider.GetError(control);
                    if (String.IsNullOrEmpty(errorMessage) == false)
                        errs.Add(new CyCustErr(errorMessage));
                }
                // Recursively call itself again to make sure that nested controls do not contain errors
                if (control.Controls.Count > 0)
                    errs.AddRange(GetControlErrors(control.Controls));
            }
            return errs;
        }
        #endregion

        #region Assigning parameters values to controls
        public void UpdateUI()
        {
            rbModeOpamp.Checked = (m_params.Mode == CyEModeType.OPAMP);
            rbModeFollower.Checked = !rbModeOpamp.Checked;

            rbOutputInternal.Checked = (m_params.OutputCurrent == CyEOutputType.OPAMP_STANDARD_1MA);
            rbOutputToPin.Checked = !rbOutputInternal.Checked;

            rbSpeedSlow.Checked = (m_params.Power == CyEPowerType.OPAMP_LOW_POWER);
            rbSpeedMedium.Checked = (m_params.Power == CyEPowerType.OPAMP_MED_POWER);
            rbSpeedHigh.Checked = (m_params.Power == CyEPowerType.OPAMP_HIGH_POWER);

            m_rbHighSpeed.Checked = (m_params.Compensation == CyECompensationType.HighSpeed);
            m_rbBalanced.Checked = (m_params.Compensation == CyECompensationType.Balanced);
            m_rbHighStability.Checked = (m_params.Compensation == CyECompensationType.HighStability);

            rb_DeepSleepEnabled.Checked = m_params.DeepSleep;
            rb_DeepSleepDisabled.Checked = !rb_DeepSleepEnabled.Checked;

            UpdateDeepSleepVisibility();
            ValidateOutputRadioButton();
        }

        private void UpdateDeepSleepVisibility()
        {
            if (m_params.IsCTBmIPV0) //PSoC4100/4200
            {
                if (m_params.DeepSleep)
                {
                    errorProvider.SetError(rb_DeepSleepEnabled, String.Format(Resources.ErrMsgDeepSleep));
                    grB_DeepSleep.Enabled = true;
                }
                else
                {
                    errorProvider.SetError(rb_DeepSleepEnabled, String.Empty);
                    grB_DeepSleep.Enabled = false;
                }
            }
            else //PSoC 4200-BL
            {
                errorProvider.SetError(rb_DeepSleepEnabled, String.Empty);
                grB_DeepSleep.Enabled = true;
            }
        }
        private void UpdateSymbolImage()
        {
            m_symbol.m_modeType = m_params.Mode;
            m_symbol.m_outputType = m_params.OutputCurrent;
            m_symbol.UpdateSymbol();
            pbSymbol.Image = m_symbol.m_bmp;
        }

        #endregion

        #region Validation

        private void ValidateOutputRadioButton()
        {
            CyCustErr err = ValidateOutputVsDeepSleep();
            errorProvider.SetError(rbOutputInternal, err.IsOK ? "" : err.Message);
        }

        /// <summary>
        /// Validates the output. 
        /// For devices with IP block m0s8pass4b (PSoC Analog Coprocessor), the 'Internal only' option is not valid 
        /// together with the Deep sleep operation enabled.
        /// </summary>
        public CyCustErr ValidateOutputVsDeepSleep()
        {
            if (m_params.IpPass4bPresent)
            {
                if (m_params.OutputCurrent == CyEOutputType.OPAMP_STANDARD_1MA && m_params.DeepSleep)
                {
                    return new CyCustErr(Resources.ErrorInternalOutputVsDeepSleep);
                }
            }
            return CyCustErr.OK;
        }
        #endregion

        #region Event handlers
        private void rb_CheckedChanged(object sender, EventArgs e)
        {
            RadioButton rb = (RadioButton) sender;
            if (rb.Checked == false)
                return;

            if (rb == rbModeOpamp)
                m_params.Mode = CyEModeType.OPAMP;
            else if (rb == rbModeFollower)
                m_params.Mode = CyEModeType.FOLLOWER;

            else if (rb == rbOutputInternal)
            {
                m_params.OutputCurrent = CyEOutputType.OPAMP_STANDARD_1MA;
                ValidateOutputRadioButton();
            }
            else if (rb == rbOutputToPin)
            {
                m_params.OutputCurrent = CyEOutputType.OPAMP_HIGH_10MA;
                ValidateOutputRadioButton();
            }

            else if (rb == rbSpeedSlow)
                m_params.Power = CyEPowerType.OPAMP_LOW_POWER;
            else if (rb == rbSpeedMedium)
                m_params.Power = CyEPowerType.OPAMP_MED_POWER;
            else if (rb == rbSpeedHigh)
                m_params.Power = CyEPowerType.OPAMP_HIGH_POWER;

            else if (rb == m_rbHighSpeed)
                m_params.Compensation = CyECompensationType.HighSpeed;
            else if (rb == m_rbBalanced)
                m_params.Compensation = CyECompensationType.Balanced;
            else if (rb == m_rbHighStability)
                m_params.Compensation = CyECompensationType.HighStability;

            else if (rb == rb_DeepSleepDisabled)
            {
                m_params.DeepSleep = false;
                UpdateDeepSleepVisibility();
                ValidateOutputRadioButton();
            }
            else if (rb == rb_DeepSleepEnabled)
            {
                m_params.DeepSleep = true;
                UpdateDeepSleepVisibility();
                ValidateOutputRadioButton();
            }
            UpdateSymbolImage();

        }
        #endregion Event handlers
    }
}
