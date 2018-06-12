/*******************************************************************************
* Copyright 2008-2014, Cypress Semiconductor Corporation. All rights reserved.
* You may use this file only in accordance with the license, terms, conditions, 
* disclaimers, and limitations in the end user license agreement accompanying 
* the software package with which this file was provided.
********************************************************************************/

using System;
using System.Collections.Generic;
using System.Windows.Forms;

namespace PWM_v3_30
{
    public partial class CyAdvancedTab : CyTabWrapper
    {
        public override string TabName
        {
            get { return CyCustomizer.ADVANCED_TAB_NAME; }
        }

        private CyConfigureTab m_configureTab;

        #region Constructor(s)
        public CyAdvancedTab(CyConfigureTab configureTab, CyParameters parameters)
            : base(parameters)
        {
            this.m_params = parameters;
            m_configureTab = configureTab;
            m_configureTab.m_advancedTab = this;
            InitializeComponent();
            InitializeGUIControls();
            m_numMinKillTime.TextChanged += m_numMinKillTime_TextChanged;
        }
        #endregion

        #region Form updating routines
        public void InitializeGUIControls()
        {
            m_cbEnableMode.DataSource = new List<string>(m_params.EnableMode.EnumDescriptionsList);
            m_cbRunMode.DataSource = new List<string>(m_params.RunMode.EnumDescriptionsList);
            m_cbTriggerMode.DataSource = new List<string>(m_params.TriggerMode.EnumDescriptionsList);
            m_cbKillMode.DataSource = new List<string>(m_params.KillMode.EnumDescriptionsList);
            m_cbCaptureMode.DataSource = new List<string>(m_params.CaptureMode.EnumDescriptionsList);

            m_numMinKillTime.Minimum = Decimal.MinValue;
            m_numMinKillTime.Maximum = Decimal.MaxValue;
        }

        public void UpdateFormFromParams()
        {
            //Set the Enable Modes Combo Box from Enums
            m_cbEnableMode.SelectedItem = m_params.EnableMode.Description;

            //Set the Run Modes Combo Box from Enums
            m_cbRunMode.SelectedItem = m_params.RunMode.Description;

            //Set the Trigger Modes Combo Box from Enums
            m_cbTriggerMode.SelectedItem = m_params.TriggerMode.Description;

            //Set the Kill Modes Combo Box from Enums
            m_cbKillMode.SelectedItem = m_params.KillMode.Description;

            //Set the Capture Modes Combo Box from Enums
            m_cbCaptureMode.SelectedItem = m_params.CaptureMode.Description;

            if (m_params.UseInterrupt)
                m_chbxNone.Checked = false;

            //Set the Fixed Function Radio Buttons Accordingly
            if (m_params.FixedFunction)
            {
                SetFixedFunction();
            }
            else
            {
                ClearFixedFunction();
            }

            //Setup Interrupt Check Boxes
            m_chbxNone.Checked = (m_params.UseInterrupt == false);

            if (m_params.KillMode.Value != CyEKillMode.B_PWM__Disabled && m_params.UseInterrupt)
            {
                m_chbxIntOnKill.Checked = m_params.InterruptOnKill;
                m_chbxIntOnKill.Enabled = true;
            }
            else
            {
                m_chbxIntOnKill.Checked = false;
                m_chbxIntOnKill.Enabled = false;
            }

            if (m_params.UseInterrupt)
            {
                m_chbxIntOnCmp1.Checked = m_params.InterruptOnCMP1;
                m_chbxIntOnTC.Checked = m_params.InterruptOnTC;
            }
            else
            {
                m_chbxIntOnCmp1.Checked = false;
                m_chbxIntOnCmp1.Enabled = false;
                m_chbxIntOnTC.Checked = false;
                m_chbxIntOnTC.Enabled = false;
            }

            if (m_params.PwmMode.Value == CyEPwmMode.B_PWM__One_Output ||
                m_params.PwmMode.Value == CyEPwmMode.B_PWM__Dither ||
                m_params.UseInterrupt)
            {
                m_chbxIntOnCmp2.Checked = false;
                m_chbxIntOnCmp2.Enabled = false;
            }
            else
            {
                m_chbxIntOnCmp2.Enabled = true;
                m_chbxIntOnCmp2.Checked = m_params.InterruptOnCMP2;
            }

            m_numMinKillTime.Text = m_params.KillTime.ToString();
            m_numMinKillTime.Enabled = (m_params.KillMode.Value == CyEKillMode.B_PWM__MinTime);

            InterruptCheckBoxUpdate();
        }
        #endregion

        #region Switching between FixedFunction and UDB
        public void SetFixedFunction()
        {
            m_params.FixedFunction = true;
            //Hide all of the fixed function block limitations
            //Set the PWM mode that is expected and then update the basic form with this information
            m_params.PwmMode.Value = CyEPwmMode.B_PWM__One_Output;

            m_cbTriggerMode.Enabled = false;
            m_params.TriggerMode.Value = CyETriggerMode.B_PWM__TMNone;
            m_cbTriggerMode.SelectedItem = m_params.TriggerMode.Description;

            m_params.DeadBand.Value = CyEDeadBandMode.B_PWM__DBMDisabled;

            m_cbKillMode.Enabled = false;
            m_params.KillMode.Value = CyEKillMode.B_PWM__Asynchronous;
            m_cbKillMode.SelectedItem = m_params.KillMode.Description;

            m_cbCaptureMode.Enabled = false;
            m_params.CaptureMode.Value = CyECaptureMode.B_PWM__None;
            m_cbCaptureMode.SelectedItem = m_params.CaptureMode.Description;

            m_cbEnableMode.Enabled = false;
            m_params.EnableMode.Value = CyEEnableMode.B_PWM__Software_Only;
            m_cbEnableMode.SelectedItem = m_params.EnableMode.Description;

            m_cbRunMode.Enabled = false;
            m_params.RunMode.Value = CyERunMode.B_PWM__Continous;
            m_cbRunMode.SelectedItem = m_params.RunMode.Description;

            m_chbxIntOnCmp2.Enabled = false;
            m_chbxIntOnCmp2.Checked = false;
            InterruptCheckBoxUpdate();
            UpdateBasicForm();
        }

        public void ClearFixedFunction()
        {
            m_params.FixedFunction = false;
            m_cbKillMode.Enabled = true;
            m_cbCaptureMode.Enabled = true;
            m_cbTriggerMode.Enabled = true;
            m_cbEnableMode.Enabled = true;
            m_cbRunMode.Enabled = true;
            m_chbxIntOnCmp2.Enabled = false;
            InterruptCheckBoxUpdate();
            UpdateBasicForm();
        }
        #endregion

        #region Control event handlers
        private void m_cbEnableMode_SelectedIndexChanged(object sender, EventArgs e)
        {
            m_params.EnableMode.Description = m_cbEnableMode.Text;
            UpdateDrawing();
        }

        private void m_cbRunMode_SelectedIndexChanged(object sender, EventArgs e)
        {
            m_params.RunMode.Description = m_cbRunMode.Text;
            UpdateDrawing();
        }

        private void m_cbTriggerMode_SelectedIndexChanged(object sender, EventArgs e)
        {
            m_params.TriggerMode.Description = m_cbTriggerMode.Text;
            UpdateDrawing();
        }

        private void m_cbKillMode_SelectedIndexChanged(object sender, EventArgs e)
        {
            m_params.KillMode.Description = m_cbKillMode.Text;

            UpdateDrawing();
            m_numMinKillTime.Enabled = (m_params.KillMode.Value == CyEKillMode.B_PWM__MinTime);

            InterruptCheckBoxUpdate();
        }

        private void m_numMinKillTime_TextChanged(object sender, EventArgs e)
        {
            byte? minKillTime = ValidateMinKillTime();
            if (minKillTime.HasValue)
            {
                m_params.KillTime = minKillTime.Value;
                UpdateDrawing();
            }
        }

        private void m_cbCaptureMode_SelectedIndexChanged(object sender, EventArgs e)
        {            
            m_params.CaptureMode.Description = m_cbCaptureMode.Text;
            UpdateDrawing();
        }

        private void UpdateBasicForm()
        {
            if (m_configureTab != null)
                m_configureTab.UpdateFormFromParams();
        }
        private void UpdateDrawing()
        {
            if (m_configureTab != null)
                m_configureTab.UpdateDrawing();
        }

        private void m_chbxNone_CheckedChanged(object sender, EventArgs e)
        {
            InterruptCheckBoxUpdate();
        }

        private void CyAdvancedTab_VisibleChanged(object sender, EventArgs e)
        {
            if (m_params.PwmMode.Value == CyEPwmMode.B_PWM__One_Output ||
                m_params.PwmMode.Value == CyEPwmMode.B_PWM__Dither)
            {
                m_chbxIntOnCmp2.Checked = false;
                m_chbxIntOnCmp2.Enabled = false;
            }
            else
            {
                m_chbxIntOnCmp2.Enabled = true;
                m_chbxIntOnCmp2.Checked = m_params.InterruptOnCMP2;
            }

            InterruptCheckBoxUpdate();
        }

        private void InterruptCheckBoxUpdate()
        {
            if (m_params.FixedFunction)
            {
                if (m_chbxNone.Checked)
                {
                    m_chbxIntOnTC.Enabled = false;
                    m_chbxIntOnTC.Checked = false;
                    m_chbxIntOnCmp1.Enabled = false;
                    m_chbxIntOnCmp1.Checked = false;
                    m_chbxIntOnCmp2.Enabled = false;
                    m_chbxIntOnCmp2.Checked = false;
                    m_chbxIntOnKill.Enabled = false;
                    m_chbxIntOnKill.Checked = false;

                    m_params.UseInterrupt = false;
                    m_params.InterruptOnTC = false;
                    m_params.InterruptOnCMP1 = false;
                    m_params.InterruptOnCMP2 = false;
                    m_params.InterruptOnKill = false;
                }
                else
                {
                    m_chbxIntOnTC.Enabled = true;
                    m_chbxIntOnCmp1.Enabled = true;
                    m_chbxIntOnCmp2.Enabled = false;
                    m_chbxIntOnKill.Enabled = false;
                    m_params.UseInterrupt = true;
                }
            }
            else
            {
                if (m_chbxNone.Checked)
                {
                    m_chbxIntOnTC.Enabled = false;
                    m_chbxIntOnTC.Checked = false;
                    m_chbxIntOnCmp1.Enabled = false;
                    m_chbxIntOnCmp1.Checked = false;
                    m_chbxIntOnCmp2.Enabled = false;
                    m_chbxIntOnCmp2.Checked = false;
                    m_chbxIntOnKill.Enabled = false;
                    m_chbxIntOnKill.Checked = false;
                    m_params.UseInterrupt = false;
                    m_params.InterruptOnTC = false;
                    m_params.InterruptOnCMP1 = false;
                    m_params.InterruptOnCMP2 = false;
                    m_params.InterruptOnKill = false;
                }
                else
                {
                    m_chbxIntOnTC.Enabled = true;
                    m_chbxIntOnCmp1.Enabled = true;
                    if (m_params.PwmMode.Value == CyEPwmMode.B_PWM__One_Output ||
                        m_params.PwmMode.Value == CyEPwmMode.B_PWM__Dither ||
                        m_params.PwmMode.Value == CyEPwmMode.B_PWM__Center_Align)
                        m_chbxIntOnCmp2.Enabled = false;
                    else
                        m_chbxIntOnCmp2.Enabled = true;

                    if (m_cbKillMode.SelectedIndex != 0)
                        m_chbxIntOnKill.Enabled = true;
                    else
                        m_chbxIntOnKill.Enabled = false;

                    m_params.UseInterrupt = true;
                }
            }
        }

        private void m_chbxIntOnTC_CheckedChanged(object sender, EventArgs e)
        {
            m_params.InterruptOnTC = ((CheckBox)sender).Checked;
        }

        private void m_chbxIntOnCmp1_CheckedChanged(object sender, EventArgs e)
        {
            m_params.InterruptOnCMP1 = ((CheckBox)sender).Checked;
        }

        private void m_chbxIntOnCmp2_CheckedChanged(object sender, EventArgs e)
        {
            m_params.InterruptOnCMP2 = ((CheckBox)sender).Checked;
        }

        private void m_chbxIntOnKill_CheckedChanged(object sender, EventArgs e)
        {
            m_params.InterruptOnKill = ((CheckBox)sender).Checked;
        }
        #endregion

        #region Validators
        byte? ValidateMinKillTime()
        {
            byte minKillTime;
            byte? result = null;
            string errorMessage = String.Format(Resources.KillTimeOutOfRange,
                                             CyParamRanges.MINKILLTIME_MIN, CyParamRanges.MINKILLTIME_MAX);
            if (byte.TryParse(m_numMinKillTime.Text, out minKillTime))
            {
                if (minKillTime >= CyParamRanges.MINKILLTIME_MIN && minKillTime <= CyParamRanges.MINKILLTIME_MAX)
                {
                    result = minKillTime;
                    errorMessage = String.Empty;
                }
            }

            m_errorProvider.SetError(m_numMinKillTime, errorMessage);

            return result;
        }
        #endregion
    }
}
