/*******************************************************************************
* Copyright 2008-2014, Cypress Semiconductor Corporation. All rights reserved.
* You may use this file only in accordance with the license, terms, conditions, 
* disclaimers, and limitations in the end user license agreement accompanying 
* the software package with which this file was provided.
********************************************************************************/

using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Drawing;
using System.Diagnostics;
using System.Data;
using System.Text;
using System.Windows.Forms;
using CyDesigner.Extensions.Common;
using CyDesigner.Extensions.Gde;

namespace Counter_v3_0
{
    public partial class CyCounterControlAdv : UserControl
    {
        ICyInstEdit_v1 m_component = null;
        public ICyTerminalQuery_v1 m_termQuery = null;
        CyCounterParameters m_params;
        bool m_ff = false;
        bool m_reloadOnCapCheckedUDB = false;
        bool m_reloadOnCompCheckedUDB = false;
        bool m_reloadOnResetCheckedUDB = false;
        bool m_reloadOnTCCheckedUDB = false;
        const string NONE = "None";
        const string CAPTUREMODENONE = "0";
        const string SOFTWAREONLY = "0";

        public CyCounterControlAdv(ICyInstEdit_v1 inst, ICyTerminalQuery_v1 termQuery, CyCounterParameters parameters)
        {
            m_component = inst;
            m_params = parameters;
            m_termQuery = termQuery;
            InitializeComponent();
            InitializeFormComponents(inst);
            UpdateFormFromParams(m_component);
        }

        private void InitializeFormComponents(ICyInstEdit_v1 inst)
        {
            //Initialize Capture Mode Combo Box with Enumerated Types
            //Set the Capture Modes Combo Box from Enums
            IEnumerable<string> CaptureModeEnums = inst.GetPossibleEnumValues(CyCounterParameters.CAPTUREMODE);
            foreach (string str in CaptureModeEnums)
            {
                m_cbCaptureMode.Items.Add(str);
            }

            //Initialize Enable Mode Combo Box with Enumerated Types
            //Set the Enable Modes Combo Box from Enums
            IEnumerable<string> EnableModeEnums = inst.GetPossibleEnumValues(CyCounterParameters.ENABLEMODE);
            foreach (string str in EnableModeEnums)
            {
                m_cbEnableMode.Items.Add(str);
            }

            //Initialize Run Mode Combo Box with Enumerated Types
            //Set the Run Modes Combo Box from Enums
            IEnumerable<string> RunModeEnums = inst.GetPossibleEnumValues(CyCounterParameters.RUNMODE);
            foreach (string str in RunModeEnums)
            {
                m_cbRunMode.Items.Add(str);
            }
        }


        public void UpdateFormFromParams(ICyInstEdit_v1 inst)
        {
            UnhookUpdateEvents();
            m_params.GetParams();

            //Set the Capture Modes Combo Box from Enums
            string paramName = null;
            CyCustErr error = CyCounterParameters.GetCaptureModeValue(inst, out paramName);
            if (m_cbCaptureMode.Items.Contains(paramName))
            {
                m_cbCaptureMode.SelectedItem = paramName;
            }
            string errorMsg = (error.IsOk) ? string.Empty : error.Message;
            ep_ErrorAdv.SetError(m_cbCaptureMode, errorMsg);


            //Set the Enable Modes Combo Box from Enums
            paramName = null;
            error = CyCounterParameters.GetEnableModeValue(inst, out paramName);
            if (m_cbEnableMode.Items.Contains(paramName))
            {
                m_cbEnableMode.SelectedItem = paramName;
            }
            errorMsg = (error.IsOk) ? string.Empty : error.Message;
            ep_ErrorAdv.SetError(m_cbEnableMode, errorMsg);


            //Set the Run Modes Combo Box from Enums
            paramName = null;
            error = CyCounterParameters.GetRunModeValue(inst, out paramName);
            if (m_cbRunMode.Items.Contains(paramName))
            {
                m_cbRunMode.SelectedItem = paramName;
            }
            errorMsg = (error.IsOk) ? string.Empty : error.Message;
            ep_ErrorAdv.SetError(m_cbRunMode, errorMsg);


            // Store old values
            m_reloadOnCapCheckedUDB = (m_params.m_reloadOnCapture.Value == CyCounterParameters.TRUE) ? true : false;
            m_reloadOnCompCheckedUDB = (m_params.m_reloadOnCompare.Value == CyCounterParameters.TRUE) ? true : false;
            m_reloadOnResetCheckedUDB = (m_params.m_reloadOnReset.Value == CyCounterParameters.TRUE) ? true : false;
            m_reloadOnTCCheckedUDB = (m_params.m_reloadOnOverUnder.Value == CyCounterParameters.TRUE) ? true : false;

            UpdateControlsAppearance();

            m_ff = (m_params.m_fixedFunction.Value == Counter_v3_0.CyCounterParameters.TRUE) ? true : false;

            //Set Interrupt on Check Boxes
            m_chbxIntSrcCapture.Checked = (m_params.m_interruptOnCapture.Value == CyCounterParameters.TRUE) ? true : false;
            m_chbxIntSrcCompare.Checked = (m_params.m_interruptOnCompare.Value == CyCounterParameters.TRUE) ? true : false;

            if (m_ff)
                m_chbxIntSrcTC.Checked = (m_params.m_interruptOnTC.Value == CyCounterParameters.TRUE) ? true : false;
            else
                m_chbxIntSrcTC.Checked = (m_params.m_interruptOnOverUnderFlow.Value == CyCounterParameters.TRUE) ?
                    true : false;

            HookupUpdateEvents();
        }

        public void UpdateControlsAppearance()
        {
            switch (m_params.m_fixedFunction.Value)
            {
                case CyCounterParameters.TRUE: SetFixedFunction(); break;
                case CyCounterParameters.FALSE: ClearFixedFunction(); break;
                default: Debug.Fail(CyCounterParameters.UNHANDLED_CASE); break;
            }
        }

        private void SetFixedFunction()
        {
            //Set Capture Mode to None
            string capturemodeff = null;
            IEnumerable<string> CaptureModesEnums = m_component.GetPossibleEnumValues(CyCounterParameters.CAPTUREMODE);
            foreach (string str in CaptureModesEnums)
            {
                if (str.Contains(NONE))
                    capturemodeff = str;
            }
            string prm = m_component.ResolveEnumDisplayToId(CyCounterParameters.CAPTUREMODE, capturemodeff);
            string captureMode = m_component.GetCommittedParam(CyCounterParameters.CAPTUREMODE).Value;
            if (captureMode != CAPTUREMODENONE)
            {
                m_params.SetAParameter(CyCounterParameters.CAPTUREMODE, prm);
            }
            m_cbCaptureMode.Enabled = false;

            //Set enable Mode to Software Only
            string enablemodeff = null;
            IEnumerable<string> EnableModesEnums = m_component.GetPossibleEnumValues(CyCounterParameters.ENABLEMODE);
            foreach (string str in EnableModesEnums)
            {
                if (str.Contains(CyCounterParameters.SOFTWARE) && str.Contains(CyCounterParameters.ONLY))
                    enablemodeff = str;
            }
            string prm2 = m_component.ResolveEnumDisplayToId(CyCounterParameters.ENABLEMODE, enablemodeff);
            string enableMode = m_component.GetCommittedParam(CyCounterParameters.ENABLEMODE).Value;
            if (enableMode != SOFTWAREONLY)
            {
                m_params.SetAParameter(CyCounterParameters.ENABLEMODE, prm2);
            }
            m_cbEnableMode.Enabled = false;

            //Set Reload On Check Boxes
            m_chbxReloadOnCapture.Visible = false;
            m_chbxReloadOnCompare.Visible = false;
            m_chbxReloadOnTC.Checked = true;
            m_chbxReloadOnTC.Enabled = false;
            m_chbxReloadOnReset.Checked = true;
            m_chbxReloadOnReset.Enabled = false;
            m_chbxIntSrcCapture.Checked = false;
            m_chbxIntSrcCapture.Enabled = false;
            string interruptOnCapture = m_component.GetCommittedParam(CyCounterParameters.INTERRUPT_ON_CAPTURE).Value;
            if (interruptOnCapture != CyCounterParameters.FALSE)
            {
                m_params.SetAParameter(CyCounterParameters.INTERRUPT_ON_CAPTURE, CyCounterParameters.FALSE);
            }
            m_chbxIntSrcCompare.Checked = false;
            m_chbxIntSrcCompare.Enabled = false;
            string interruptOnCompare = m_component.GetCommittedParam(CyCounterParameters.INTERRUPT_ON_COMPARE).Value;
            if (interruptOnCompare != CyCounterParameters.FALSE)
            {
                m_params.SetAParameter(CyCounterParameters.INTERRUPT_ON_COMPARE, CyCounterParameters.FALSE);
            }
        }

        private void ClearFixedFunction()
        {
            m_cbCaptureMode.Enabled = true;
            m_cbEnableMode.Enabled = true;

            m_chbxReloadOnCapture.Checked = m_reloadOnCapCheckedUDB;
            m_chbxReloadOnCapture.Visible = true;

            m_chbxReloadOnCompare.Checked = m_reloadOnCompCheckedUDB;
            m_chbxReloadOnCompare.Visible = true;

            m_chbxReloadOnTC.Checked = m_reloadOnTCCheckedUDB;
            m_chbxReloadOnTC.Enabled = true;

            m_chbxReloadOnReset.Checked = m_reloadOnResetCheckedUDB;
            m_chbxReloadOnReset.Enabled = true;

            m_chbxIntSrcCapture.Enabled = true;
            m_chbxIntSrcCompare.Enabled = true;
        }

        void UpdateCheckBoxParameter(string paramName, bool isChecked, bool visible)
        {
            if (isChecked && visible)
                m_params.SetAParameter(paramName, CyCounterParameters.TRUE);
            else
                m_params.SetAParameter(paramName, CyCounterParameters.FALSE);
        }

        private void m_chbxReloadOnCapture_Changed(object sender, EventArgs e)
        {
            CheckBox cb = (CheckBox)sender;
            UpdateCheckBoxParameter(CyCounterParameters.RELOAD_ON_CAPTURE, cb.Checked, cb.Visible);
        }

        private void m_chbxReloadOnCompare_Changed(object sender, EventArgs e)
        {
            CheckBox cb = (CheckBox)sender;
            UpdateCheckBoxParameter(CyCounterParameters.RELOAD_ON_COMPARE, cb.Checked, cb.Visible);
        }

        private void m_chbxReloadOnReset_Changed(object sender, EventArgs e)
        {
            CheckBox cb = (CheckBox)sender;
            m_params.SetAParameter(CyCounterParameters.RELOAD_ON_RESET, cb.Checked.ToString());
        }

        private void m_chbxReloadOnTC_Changed(object sender, EventArgs e)
        {
            CheckBox cb = (CheckBox)sender;
            m_params.SetAParameter(CyCounterParameters.RELOAD_ON_OVERUNDER, cb.Checked.ToString());
        }

        private void m_chbxIntSrcTC_Changed(object sender, EventArgs e)
        {
            CheckBox cb = (CheckBox)sender;
            bool bOnTc = false;
            bool bOnOverTc = false;
            if (m_ff)
            {
                bOnTc = cb.Checked;
            }
            else
            {
                bOnOverTc = cb.Checked;
            }

            UpdateCheckBoxParameter(CyCounterParameters.INTERRUPT_ON_TC, bOnTc, cb.Visible);
            UpdateCheckBoxParameter(CyCounterParameters.INTERRUPT_ON_OVER_UNDERFLOW, bOnOverTc, cb.Visible);
        }

        private void m_chbxIntSrcCapture_Changed(object sender, EventArgs e)
        {
            CheckBox cb = (CheckBox)sender;
            UpdateCheckBoxParameter(CyCounterParameters.INTERRUPT_ON_CAPTURE, cb.Checked, cb.Visible);
        }

        private void m_chbxIntSrcCompare_Changed(object sender, EventArgs e)
        {
            CheckBox cb = (CheckBox)sender;
            UpdateCheckBoxParameter(CyCounterParameters.INTERRUPT_ON_COMPARE, cb.Checked, cb.Visible);
        }

        void UnhookUpdateEvents()
        {
            m_cbCaptureMode.SelectedIndexChanged -= m_cbCaptureMode_SelectedIndexChanged;
            m_cbEnableMode.SelectedIndexChanged -= m_cbEnableMode_SelectedIndexChanged;
            m_cbRunMode.SelectedIndexChanged -= m_cbRunMode_SelectedIndexChanged;
            m_chbxReloadOnCapture.VisibleChanged -= m_chbxReloadOnCapture_Changed;
            m_chbxReloadOnCapture.CheckedChanged -= m_chbxReloadOnCapture_Changed;
            m_chbxReloadOnCompare.VisibleChanged -= m_chbxReloadOnCompare_Changed;
            m_chbxReloadOnCompare.CheckedChanged -= m_chbxReloadOnCompare_Changed;
            m_chbxIntSrcTC.VisibleChanged -= m_chbxIntSrcTC_Changed;
            m_chbxIntSrcTC.CheckedChanged -= m_chbxIntSrcTC_Changed;
            m_chbxIntSrcCapture.VisibleChanged -= m_chbxIntSrcCapture_Changed;
            m_chbxIntSrcCapture.CheckedChanged -= m_chbxIntSrcCapture_Changed;
            m_chbxIntSrcCompare.VisibleChanged -= m_chbxIntSrcCompare_Changed;
            m_chbxIntSrcCompare.CheckedChanged -= m_chbxIntSrcCompare_Changed;
        }

        void HookupUpdateEvents()
        {
            m_cbCaptureMode.SelectedIndexChanged += m_cbCaptureMode_SelectedIndexChanged;
            m_cbEnableMode.SelectedIndexChanged += m_cbEnableMode_SelectedIndexChanged;
            m_cbRunMode.SelectedIndexChanged += m_cbRunMode_SelectedIndexChanged;
            m_chbxReloadOnCapture.VisibleChanged += m_chbxReloadOnCapture_Changed;
            m_chbxReloadOnCapture.CheckedChanged += m_chbxReloadOnCapture_Changed;
            m_chbxReloadOnCompare.VisibleChanged += m_chbxReloadOnCompare_Changed;
            m_chbxReloadOnCompare.CheckedChanged += m_chbxReloadOnCompare_Changed;
            m_chbxIntSrcTC.VisibleChanged += m_chbxIntSrcTC_Changed;
            m_chbxIntSrcTC.CheckedChanged += m_chbxIntSrcTC_Changed;
            m_chbxIntSrcCapture.VisibleChanged += m_chbxIntSrcCapture_Changed;
            m_chbxIntSrcCapture.CheckedChanged += m_chbxIntSrcCapture_Changed;
            m_chbxIntSrcCompare.VisibleChanged += m_chbxIntSrcCompare_Changed;
            m_chbxIntSrcCompare.CheckedChanged += m_chbxIntSrcCompare_Changed;
        }


        private void m_cbCaptureMode_SelectedIndexChanged(object sender, EventArgs e)
        {
            string prm = m_component.ResolveEnumDisplayToId(CyCounterParameters.CAPTUREMODE, m_cbCaptureMode.Text);
            m_params.SetAParameter(CyCounterParameters.CAPTUREMODE, prm);
        }

        private void m_cbEnableMode_SelectedIndexChanged(object sender, EventArgs e)
        {
            string prm = m_component.ResolveEnumDisplayToId(CyCounterParameters.ENABLEMODE, m_cbEnableMode.Text);
            m_params.SetAParameter(CyCounterParameters.ENABLEMODE, prm);
        }

        private void m_cbRunMode_SelectedIndexChanged(object sender, EventArgs e)
        {
            string prm = m_component.ResolveEnumDisplayToId(CyCounterParameters.RUNMODE, m_cbRunMode.Text);
            m_params.SetAParameter(CyCounterParameters.RUNMODE, prm);
        }
    }
}
