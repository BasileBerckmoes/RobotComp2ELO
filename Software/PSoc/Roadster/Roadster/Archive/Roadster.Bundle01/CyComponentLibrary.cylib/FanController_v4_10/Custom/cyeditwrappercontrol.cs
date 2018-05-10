/*******************************************************************************
* Copyright 2008-2014, Cypress Semiconductor Corporation.  All rights reserved.
* You may use this file only in accordance with the license, terms, conditions,
* disclaimers, and limitations in the end user license agreement accompanying
* the software package with which this file was provided.
********************************************************************************/


using System;
using System.Collections.Generic;
using System.Text;
using CyDesigner.Extensions.Gde;
using CyDesigner.Extensions.Common;
using System.ComponentModel;
using System.Windows.Forms;
using System.Reflection;


namespace FanController_v4_10
{
    /// <summary>
    /// Wrapper for tabs
    /// </summary>
    public class CyEditingWrapperControl : UserControl, ICyParamEditingControl
    {
        protected CyParameters m_prms = null;
        protected ErrorProvider m_errorProvider = null;

        public virtual string TabName
        {
            get { return String.Empty; }
        }

        public CyEditingWrapperControl()
        {
        }

        public CyEditingWrapperControl(CyParameters parameters)
        {
            m_prms = parameters;

            m_errorProvider = new ErrorProvider();
            m_errorProvider.BlinkStyle = ErrorBlinkStyle.NeverBlink;

            this.AutoScroll = true;
            this.Dock = DockStyle.Fill;
        }

        #region ICyParamEditingControl Members
        public Control DisplayControl
        {
            get { return this; }
        }

        // Gets any errors that exist for parameters on the DisplayControl.
        public virtual IEnumerable<CyCustErr> GetErrors()
        {
            List<CyCustErr> errs = new List<CyCustErr>();
            if (m_prms.m_instQuery != null)
            {
                foreach (string paramName in m_prms.m_instQuery.GetParamNames())
                {
                    CyCompDevParam param = m_prms.m_instQuery.GetCommittedParam(paramName);
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
            }
            errs.AddRange(CheckControlForErrors(this.Controls));
            return errs;
        }

        /// <summary>
        /// Recursive function that returns all errors from errorProvider
        /// </summary>
        private List<CyCustErr> CheckControlForErrors(ControlCollection controls)
        {
            string errorMessage = string.Empty;
            List<CyCustErr> errs = new List<CyCustErr>();

            if (m_errorProvider == null)
                return errs;

            foreach (Control control in controls)
            {
                if (control.Enabled) // Check only active controls
                {
                    errorMessage = m_errorProvider.GetError(control);
                    if (string.IsNullOrEmpty(errorMessage) == false)
                        errs.Add(new CyCustErr(errorMessage));

                    if (control.Controls.Count > 0)
                        errs.AddRange(CheckControlForErrors(control.Controls));
                }
            }
            return errs;
        }
        #endregion
    }
}
