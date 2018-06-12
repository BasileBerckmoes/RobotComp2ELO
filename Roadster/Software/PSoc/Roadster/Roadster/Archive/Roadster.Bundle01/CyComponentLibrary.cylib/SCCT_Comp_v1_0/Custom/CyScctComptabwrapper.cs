/*******************************************************************************
* Copyright 2013, Cypress Semiconductor Corporation.  All rights reserved.
* You may use this file only in accordance with the license, terms, conditions, 
* disclaimers, and limitations in the end user license agreement accompanying 
* the software package with which this file was provided. 
********************************************************************************/

using System;
using System.Collections.Generic;
using System.Diagnostics;
using System.Windows.Forms;
using CyDesigner.Extensions.Common;
using CyDesigner.Extensions.Gde;

namespace SCCT_Comp_v1_0
{
    public class CyScctCompTabWrapper : UserControl, ICyParamEditingControl
    {
        protected CyScctCompParameters m_params = null;
        protected ErrorProvider m_errorProvider = null;
        protected string m_tabName = "Empty";

        public string TabName
        {
            get { return m_tabName; }
        }

        public CyScctCompTabWrapper() { }
        public CyScctCompTabWrapper(CyScctCompParameters parameters, string sTabName)
        {
            if (parameters != null && !string.IsNullOrEmpty(sTabName))
            {
                m_params = parameters;
                m_tabName = sTabName;
                m_errorProvider = new ErrorProvider();
                m_errorProvider.BlinkStyle = ErrorBlinkStyle.NeverBlink;
                this.Load += new EventHandler(CyEditingWrapperControl_Load);
            }
            else Debug.Assert(false);
        }

        void CyEditingWrapperControl_Load(object sender, EventArgs e)
        {
            this.Dock = DockStyle.Fill;
            this.AutoScroll = true;
        }

        #region ICyParamEditingControl Members
        public Control DisplayControl
        {
            get { return this; }
        }

        // Gets any errors that exist for parameters on the DisplayControl.
        public IEnumerable<CyCustErr> GetErrors()
        {
            List<CyCustErr> errs = new List<CyCustErr>();

            if (m_errorProvider != null)
                errs = CheckControlForErrors(this.Controls);

            foreach (string paramName in m_params.m_inst.GetParamNames())
            {
                CyCompDevParam param = m_params.m_inst.GetCommittedParam(paramName);
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

        private List<CyCustErr> CheckControlForErrors(ControlCollection controls)
        {
            string errorMessage = string.Empty;
            List<CyCustErr> errs = new List<CyCustErr>();

            foreach (Control control in controls)
            {
                errorMessage = m_errorProvider.GetError(control);
                if (string.IsNullOrEmpty(errorMessage) == false)
                    errs.Add(new CyCustErr(errorMessage));

                if (control.Controls.Count > 0)
                    errs.AddRange(CheckControlForErrors(control.Controls));
            }
            return errs;
        }
        #endregion
    }
}
