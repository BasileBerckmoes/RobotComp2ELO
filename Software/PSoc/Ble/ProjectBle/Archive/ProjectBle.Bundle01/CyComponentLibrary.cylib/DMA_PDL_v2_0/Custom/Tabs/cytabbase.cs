/*******************************************************************************
* Copyright 2016-2017, Cypress Semiconductor Corporation.  All rights reserved.
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

namespace DMA_PDL_v2_0.Tabs
{
    internal interface ICyTab
    {
        /// <summary>
        /// Canonical name of the tab.
        /// </summary>
        string TabName { get; }

        /// <summary>
        /// Updates GUI controls with the values from the parameters.
        /// </summary>
        void UpdateUI();
    }

    internal class CyTabBase : UserControl, ICyParamEditingControl
    {
        #region Protected members
        protected readonly CyParameters m_parameters;
        protected readonly ErrorProvider m_errorProvider;
        #endregion

        #region Constructor(s)
        /// <summary>
        /// This constructor intended for correct control appearance in the designer mode.
        /// </summary>
        private CyTabBase() { }

        public CyTabBase(CyParameters parameters)
        {
            this.m_parameters = parameters;
            this.m_errorProvider = new ErrorProvider();
            this.m_errorProvider.BlinkStyle = ErrorBlinkStyle.NeverBlink;
            this.Dock = DockStyle.Fill;
            this.AutoScroll = true;
        }
        #endregion

        #region ICyParamEditingControl members
        public Control DisplayControl
        {
            get { return this; }
        }

        public virtual IEnumerable<CyCustErr> CheckControlsForErrors()
        {
            return CheckControlsForErrors(this.Controls);
        }

        private IEnumerable<CyCustErr> CheckControlsForErrors(ControlCollection controls)
        {
            if (m_errorProvider != null)
            {
                foreach (Control control in controls)
                {
                    if (control.Enabled == false)
                        continue;

                    string errMsg = m_errorProvider.GetError(control);
                    if (String.IsNullOrEmpty(errMsg) == false)
                        yield return new CyCustErr(errMsg);

                    // Recursively call itself again to make sure that nested controls do not contain errors
                    if (control.Controls.Count > 0)
                        foreach (CyCustErr err in CheckControlsForErrors(control.Controls))
                            yield return err;
                }
            }
        }

        /// <summary>
        /// Gets error provider and parameters errors.
        /// </summary>
        public IEnumerable<CyCustErr> GetErrors()
        {
            Debug.Assert(this is ICyTab, String.Format("Class {0} must implement {1} interface.",
                this.Name, typeof(ICyTab).Name));

            // Extract errors from error providers that are currently visible
            foreach (CyCustErr err in CheckControlsForErrors())
            {
                yield return err;
            }

            // Look for errors in parameters
            string tabName = (this as ICyTab).TabName;
            foreach (string paramName in m_parameters.InstQuery.GetParamNames())
            {
                CyCompDevParam param = m_parameters.InstQuery.GetCommittedParam(paramName);
                if (param.TabName.Equals(tabName))
                {
                    if (param.ErrorCount > 0)
                    {
                        foreach (string errMsg in param.Errors)
                        {
                            yield return new CyCustErr(errMsg);
                        }
                    }
                }
            }
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
                if (control.Enabled)
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
    }
}
