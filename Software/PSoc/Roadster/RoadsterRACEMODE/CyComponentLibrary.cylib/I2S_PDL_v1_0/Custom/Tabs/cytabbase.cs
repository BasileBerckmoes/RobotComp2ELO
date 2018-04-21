/*******************************************************************************
* Copyright 2016, Cypress Semiconductor Corporation.  All rights reserved.
* You may use this file only in accordance with the license, terms, conditions, 
* disclaimers, and limitations in the end user license agreement accompanying 
* the software package with which this file was provided. 
********************************************************************************/

using System;
using System.Diagnostics;
using System.Windows.Forms;
using System.Collections.Generic;
using CyDesigner.Extensions.Gde;
using CyDesigner.Extensions.Common;

namespace I2S_PDL_v1_0.Tabs
{
    internal class CyTabBase : UserControl, ICyParamEditingControl
    {
        #region Protected members
        protected readonly CyParameters m_params = null;
        protected readonly ErrorProvider m_errorProvider = null;
        #endregion

        #region Constructor(s)
        /// <summary>
        /// This constructor intended for correct control appearance in the designer mode.
        /// </summary>
        private CyTabBase() { }

        public CyTabBase(CyParameters parameters, string tabName, string tabDisplayName)
        {
            TabName = tabName;
            TabDisplayName = tabDisplayName;
            m_params = parameters;
            m_errorProvider = new ErrorProvider();
            m_errorProvider.BlinkStyle = ErrorBlinkStyle.NeverBlink;
            Dock = DockStyle.Fill;
            AutoScroll = true;
        }
        #endregion

        #region ICyParamEditingControl members
        public Control DisplayControl
        {
            get { return this; }
        }

        /// <summary>
        /// Gets error provider and parameters errors.
        /// </summary>
        public IEnumerable<CyCustErr> GetErrors()
        {
            List<CyCustErr> errs = new List<CyCustErr>();
            errs = GetControlErrors(this.Controls);

            // Look for errors in parameters
            string tabName = TabName;
            foreach (string paramName in m_params.InstQuery.GetParamNames())
            {
                CyCompDevParam param = m_params.InstQuery.GetCommittedParam(paramName);
                if (param.TabName.Equals(tabName))
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

        #region Visibility
        private const string INVISIBLE_TAG = "Invisible";
        /// <summary>
        /// This function is used to set Visibility property for controls. It sets additionally the Tag value, 
        /// so the customizer can distinguish if a control is really hidden or just invisible at that moment  
        /// (it may happen if another tab is selected).
        /// </summary>
        protected void SetVisible(Control c, bool isVisible)
        {
            c.Visible = isVisible;
            c.Tag = isVisible ? null : INVISIBLE_TAG;
        }

        /// <summary>
        /// Gets a value indicating whether the control is hidden.
        /// </summary>
        protected bool IsControlHidden(Control c)
        {
            return (c.Visible == false) && (c.Tag != null) && (c.Tag.ToString() == INVISIBLE_TAG);
        }
        #endregion

        #region Controls errors check method(s)
        /// <summary>
        /// Clears the error provider error for the specified control.
        /// </summary>
        protected void ClearError(Control control)
        {
            m_errorProvider.SetError(control, String.Empty);
        }

        /// <summary>
        /// Sets the error provider error for the specified control.
        /// </summary>
        protected void SetError(Control control, string errorMessage)
        {
            m_errorProvider.SetError(control, errorMessage);
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
                if (control.Enabled && (IsControlHidden(control) == false))
                {
                    errorMessage = m_errorProvider.GetError(control);
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

        #region ICyTab members
        public string TabName { set; get; }
        public string TabDisplayName { set; get; }
        public virtual void UpdateUI()
        {
            Debug.Assert(false, "Calling of the CyTabBase virtual method");
        }
        #endregion
    }
}
