/*******************************************************************************
* Copyright 2015, Cypress Semiconductor Corporation. All rights reserved.
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
using System.Diagnostics;

namespace RTC_P4_v1_20
{
    public class CyTabControlWrapper : UserControl, ICyParamEditingControl
    {
        protected CyParameters m_params = null;
        protected ErrorProvider m_errorProvider = null;
        protected ErrorProvider m_warningProvider = null;

        public virtual string TabName
        {
            get
            {
                Debug.Fail("TabName should be overriden"); 
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

            m_warningProvider = new ErrorProvider();
            m_warningProvider.BlinkStyle = ErrorBlinkStyle.NeverBlink;
            m_warningProvider.Icon = Resource.IconWarning;

            this.Dock = DockStyle.Fill;
            this.AutoScroll = true;
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
                foreach (Control control in this.Controls)
                {
                    errorMessage = m_errorProvider.GetError(control);
                    if (string.IsNullOrEmpty(errorMessage) == false)
                        errs.Add(new CyCustErr(errorMessage));

                    // Check controls inside groupbox
                    foreach (Control internalControl in control.Controls)
                    {
                        errorMessage = m_errorProvider.GetError(internalControl);
                        if (string.IsNullOrEmpty(errorMessage) == false)
                            errs.Add(new CyCustErr(errorMessage));

                        // Check controls inside flowlayoutpanel inside groupbox
                        foreach (Control internalInternalControl in internalControl.Controls)
                        {
                            errorMessage = m_errorProvider.GetError(internalInternalControl);
                            if (string.IsNullOrEmpty(errorMessage) == false)
                                errs.Add(new CyCustErr(errorMessage));
                        }
                    }
                }
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
