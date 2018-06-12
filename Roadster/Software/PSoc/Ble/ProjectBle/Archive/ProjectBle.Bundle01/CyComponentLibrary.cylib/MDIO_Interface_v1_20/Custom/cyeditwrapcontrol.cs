/*******************************************************************************
* Copyright 2013-2014, Cypress Semiconductor Corporation.  All rights reserved.
* You may use this file only in accordance with the license, terms, conditions,
* disclaimers, and limitations in the end user license agreement accompanying
* the software package with which this file was provided.
********************************************************************************/

using System;
using System.Collections.Generic;
using System.Windows.Forms;
using CyDesigner.Extensions.Common;
using CyDesigner.Extensions.Gde;

namespace MDIO_Interface_v1_20
{
    public class CyEditingWrapperControl : UserControl, ICyParamEditingControl
    {
        protected CyParameters m_params = null;
        protected ErrorProvider m_errorProvider = null;

        public virtual string TabName
        {
            get { return "Empty"; }
        }

        #region Constructor(s)
        public CyEditingWrapperControl() { }
        public CyEditingWrapperControl(CyParameters prms)
        {
            m_params = prms;
            m_errorProvider = new ErrorProvider();
            m_errorProvider.BlinkStyle = ErrorBlinkStyle.NeverBlink;
            this.Dock = DockStyle.Fill;
            this.AutoScroll = true;
        }
        #endregion

        #region Data grid methods
        protected void CommitCellValueImmediately(DataGridView dataGridView)
        {
            if (dataGridView.CurrentCell != null)
            {
                if (dataGridView.CurrentCell.GetType() == typeof(DataGridViewCheckBoxCell))
                {
                    if (dataGridView.IsCurrentCellDirty)
                    {
                        dataGridView.CommitEdit(DataGridViewDataErrorContexts.Commit);
                    }
                }
            }
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

            // Look for errors on Basic tab
            if (this.TabName == CyCustomizer.GENERAL_TAB_NAME)
            {
                errs = CheckControlForErrors(this.Controls);
            }

            // Look for errors in register spaces
            if (this.TabName == CyCustomizer.ADVANCED_TAB_NAME)
            {
                for (int i = 0; i < m_params.m_regSpaceList.m_regSpaces.Count; i++)
                {
                    string errorText = m_params.m_regSpaceList.GetNameError(m_params.m_regSpaceList.m_regSpaces[i]);
                    if (errorText != String.Empty)
                    {
                        errs.Add(new CyCustErr(String.Format("{0}: {1}",
                                               m_params.m_regSpaceList.m_regSpaces[i].Name, errorText.ToLower())));
                    }
                }
                errs.AddRange(m_params.m_regSpaceList.GetRegSpacesErrors());
            }

            // Look for errors in parameters
            foreach (string paramName in m_params.m_query.GetParamNames())
            {
                CyCompDevParam param = m_params.m_query.GetCommittedParam(paramName);
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
                // Recursively call itself again to make sure that nested controls does not contain errors
                if (control.Controls.Count > 0)
                    errs.AddRange(CheckControlForErrors(control.Controls));
            }
            return errs;
        }
        #endregion
    }
}
