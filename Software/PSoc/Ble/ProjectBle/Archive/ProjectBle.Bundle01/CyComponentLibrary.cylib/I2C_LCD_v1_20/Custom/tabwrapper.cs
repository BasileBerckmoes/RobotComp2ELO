/*******************************************************************************
* Copyright 2014, Cypress Semiconductor Corporation.  All rights reserved.
* You may use this file only in accordance with the license, terms, conditions, 
* disclaimers, and limitations in the end user license agreement accompanying 
* the software package with which this file was provided. 
********************************************************************************/

using System;
using System.Collections.Generic;
using System.Windows.Forms;
using CyDesigner.Extensions.Common;
using CyDesigner.Extensions.Gde;

namespace I2C_LCD_v1_20
{
    public class CyTabWrapper : UserControl, ICyParamEditingControl
    {
        protected CyParameters m_params = null;
        protected ErrorProvider m_errorProvider = null;

        public virtual string TabName
        {
            get { return "Empty"; }
        }

        #region Constructor(s)
        public CyTabWrapper() { }
        public CyTabWrapper(CyParameters parameters)
        {
            m_params = parameters;
            this.m_errorProvider = new ErrorProvider();
            this.m_errorProvider.BlinkStyle = ErrorBlinkStyle.NeverBlink;
            this.Dock = DockStyle.Fill;
            this.AutoScroll = true;
        }
        #endregion

        #region ICyParamEditingControl Members
        public Control DisplayControl
        {
            get { return this; }
        }

        // Gets any errors that exist for parameters on the DisplayControl.
        public IEnumerable<CyCustErr> GetErrors()
        {
            List<CyCustErr> errs = new List<CyCustErr>();

            // Look for errors on General tab
            if (this.TabName == CyCustomizer.GENERAL_TAB_NAME || this.TabName == CyCustomizer.CUSTOM_COMMANDS_TAB_NAME)
            {
                errs = CheckControlForErrors(this.Controls);
            }

            // Look for errors in parameters
            foreach (string paramName in m_params.InstQuery.GetParamNames())
            {
                CyCompDevParam param = m_params.InstQuery.GetCommittedParam(paramName);
                if (param.TabName.Equals(this.TabName))
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

        #region Controls errors check methods
        private List<CyCustErr> CheckControlForErrors(ControlCollection controls)
        {
            string errorMessage = String.Empty;
            List<CyCustErr> errs = new List<CyCustErr>();
            foreach (Control control in controls)
            {
                if (control is DataGridView)
                {
                    if (CheckDataGridForErrors((DataGridView)control))
                    {
                        if (control.Tag != null && control.Tag.ToString() == CyCustomCommandsTab.REQUIRED_COMMANDS)
                        {
                            errs.Add(new CyCustErr(Resources.RequiredCommandsDataGridContainsError));
                        }
                        else
                        {
                            errs.Add(new CyCustErr(Resources.CustomCommandsDataGridContainsError));
                        }
                    }
                }
                else
                {
                    errorMessage = m_errorProvider.GetError(control);
                    if (String.IsNullOrEmpty(errorMessage) == false)
                        errs.Add(new CyCustErr(errorMessage));
                    // Recursively call itself again to make sure that nested controls does not contain errors
                    if (control.Controls.Count > 0)
                        errs.AddRange(CheckControlForErrors(control.Controls));
                }
            }
            return errs;
        }

        private bool CheckDataGridForErrors(DataGridView dgv)
        {
            bool containsError = false;
            if (dgv != null)
            {
                for (int i = 0; i < dgv.RowCount; i++)
                {
                    for (int j = 0; j < dgv.ColumnCount; j++)
                    {
                        if (String.IsNullOrEmpty(dgv[j, i].ErrorText) == false)
                        {
                            containsError = true;
                            break;
                        }
                    }
                    if (containsError)
                    {
                        break;
                    }
                }
            }
            return containsError;
        }
        #endregion
    }
}
