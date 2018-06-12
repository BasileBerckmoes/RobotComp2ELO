/*******************************************************************************
* Copyright 2016, Cypress Semiconductor Corporation. All rights reserved.
* You may use this file only in accordance with the license, terms, conditions, 
* disclaimers, and limitations in the end user license agreement accompanying 
* the software package with which this file was provided.
********************************************************************************/

using System;
using System.Collections.Generic;
using System.Windows.Forms;
using CyDesigner.Extensions.Common;
using CyDesigner.Extensions.Gde;

namespace CSD_Comp_P4_v1_0
{
    public class CyTabControlWrapper : UserControl, ICyParamEditingControl
    {
        #region Class Consts

        public const string VOLTAGE_DISPLAY_FORMAT_GUI = "0.00";
        public const string VOLTAGE_DISPLAY_FORMAT_ERRMSG = "0.##";

        #endregion Class Consts

        protected CyParameters m_params = null;
        protected ErrorProvider m_errorProvider = null;

        public virtual string TabName
        {
            get
            {
                return "Empty";
            }
        }

        public CyTabControlWrapper()
        {
        }

        public CyTabControlWrapper(CyParameters param)
        {
            m_params = param;

            m_errorProvider = new ErrorProvider();
            m_errorProvider.BlinkStyle = ErrorBlinkStyle.NeverBlink;

            this.Dock = DockStyle.Fill;
            this.AutoScroll = true;
        }

        private List<CyCustErr> CheckControlForErrors(ControlCollection controls)
        {
            string errorMessage = String.Empty;
            List<CyCustErr> errs = new List<CyCustErr>();
            foreach (Control control in controls)
            {
                errorMessage = m_errorProvider.GetError(control);
                if (String.IsNullOrEmpty(errorMessage) == false)
                    errs.Add(new CyCustErr(errorMessage));
                // Recursively call itself again to make sure that nested controls don't contain errors
                if (control.Controls.Count > 0)
                    errs.AddRange(CheckControlForErrors(control.Controls));
            }
            return errs;
        }

        #region ICyParamEditingControl Members

        public Control DisplayControl
        {
            get { return this; }
        }

        public virtual IEnumerable<CyCustErr> GetErrors()
        {
            List<CyCustErr> errs = new List<CyCustErr>();
            string errorMessage = string.Empty;

            if (m_errorProvider != null)
            {
                // Check controls for errors
                errs = CheckControlForErrors(this.Controls);
            }

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

        #endregion
    }
}
