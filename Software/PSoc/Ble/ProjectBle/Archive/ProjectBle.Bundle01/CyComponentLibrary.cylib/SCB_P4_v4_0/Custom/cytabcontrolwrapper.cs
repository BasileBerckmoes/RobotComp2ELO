/*******************************************************************************
* Copyright 2012-2017, Cypress Semiconductor Corporation.  All rights reserved.
* You may use this file only in accordance with the license, terms, conditions, 
* disclaimers, and limitations in the end user license agreement accompanying 
* the software package with which this file was provided.
********************************************************************************/

using System;
using System.Collections.Generic;
using System.Windows.Forms;
using CyDesigner.Extensions.Common;
using CyDesigner.Extensions.Gde;

namespace SCB_P4_v4_0
{
    public partial class CyTabControlWrapper : UserControl, ICyParamEditingControl
    {
        protected readonly ICyTabbedParamEditor m_editor = null;
        protected CyParameters m_params = null;
        protected ErrorProvider m_errorProvider = null;
        protected ErrorProvider m_warningProvider = null;
        protected ErrorProvider m_noteProvider = null;
        protected bool m_isVisible = false;

        /// <summary>
        /// This property returns the tab name that will be associated with parameters in expression view.
        /// </summary>
        public virtual string TabName
        {
            get { return string.Empty; }
        }

        /// <summary>
        /// This property returns the name that will be displayed as tab title.
        /// </summary>
        public virtual string TabDisplayName
        {
            get { return string.Empty; }
        }

        /// <summary>
        /// This is method that updates UI from the parameters.
        /// </summary>
        public virtual void UpdateUI() { }

        #region Constructor(s)
        public CyTabControlWrapper() { }
        public CyTabControlWrapper(CyParameters prms, ICyTabbedParamEditor editor)
        {
            m_params = prms;
            m_editor = editor;

            m_errorProvider = new ErrorProvider();
            m_errorProvider.BlinkStyle = ErrorBlinkStyle.NeverBlink;
            m_warningProvider = new ErrorProvider();
            m_warningProvider.BlinkStyle = ErrorBlinkStyle.NeverBlink;
            m_warningProvider.Icon = Resources.WarningIco;
            m_noteProvider = new ErrorProvider();
            m_noteProvider.BlinkStyle = ErrorBlinkStyle.NeverBlink;
            m_noteProvider.Icon = Resources.InformationIconIco;

            this.Dock = DockStyle.Fill;
            this.AutoScroll = true;
        }
        #endregion

        #region Tab appearance
        protected void ShowTab()
        {
            m_editor.ShowCustomPage(this.TabDisplayName);
            m_isVisible = true;
        }

        protected void HideTab()
        {
            m_editor.HideCustomPage(this.TabDisplayName);
            m_isVisible = false;
        }

        protected void SelectTab()
        {
            if (m_params.GlobalEditMode == false && m_params.SCBMode != CyESCBMode.UNCONFIG)
            {
                if (m_params.IsScbIPV1 && m_params.SCBMode == CyESCBMode.SPI && m_params.SCBMode == CyESCBMode.UART)
                {
                    // Keep general tab opened since SPI and UART modes are not supported.
                }
                else
                {
                    if (m_isVisible)
                        m_editor.SetSelectedPage(this.TabDisplayName);
                }
            }
        }
        #endregion

        #region Error/Warning/Note provider methods

        /// <summary>
        /// Clears error, warning and note notifications that are displayed next to the specific control.
        /// </summary>
        /// <param name="control">Control which notifications should be cleared.</param>
        protected void ClearNotifications(Control control)
        {
            m_errorProvider.SetError(control, String.Empty);
            m_warningProvider.SetError(control, String.Empty);
            m_noteProvider.SetError(control, String.Empty);
        }

        #endregion

        #region ICyParamEditingControl Members
        public Control DisplayControl
        {
            get { return this; }
        }

        public virtual IEnumerable<CyCustErr> GetErrors()
        {
            List<CyCustErr> errs = new List<CyCustErr>();
            if (m_isVisible)
            {
                // Extract errors from error providers that are currently visible
                errs.AddRange(CheckControlsForErrors(this.Controls));

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
            }
            return errs;
        }

        protected virtual List<CyCustErr> CheckControlsForErrors(ControlCollection controls)
        {
            string errorMessage = String.Empty;
            List<CyCustErr> errs = new List<CyCustErr>();
            if (m_errorProvider != null)
            {
                foreach (Control control in controls)
                {
                    errorMessage = m_errorProvider.GetError(control);
                    if (String.IsNullOrEmpty(errorMessage) == false)
                        errs.Add(new CyCustErr(errorMessage));
                    // Recursively call itself again to make sure that nested controls does not contain errors
                    if (control.Controls.Count > 0)
                        errs.AddRange(CheckControlsForErrors(control.Controls));
                }
            }
            return errs;
        }
        #endregion
    }
}
