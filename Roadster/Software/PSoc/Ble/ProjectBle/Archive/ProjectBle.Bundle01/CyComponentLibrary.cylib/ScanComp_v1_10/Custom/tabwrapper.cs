/*******************************************************************************
* Copyright 2013, Cypress Semiconductor Corporation.  All rights reserved.
* You may use this file only in accordance with the license, terms, conditions, 
* disclaimers, and limitations in the end user license agreement accompanying 
* the software package with which this file was provided. 
********************************************************************************/

using System;
using System.Collections.Generic;
using System.Windows.Forms;
using CyDesigner.Extensions.Common;
using CyDesigner.Extensions.Gde;

namespace ScanComp_v1_10
{
    public class CyTabWrapper : UserControl, ICyParamEditingControl
    {
        protected CyParameters m_params = null;
        protected ErrorProvider m_errorProvider = null;

        // Enumeration is used to know the DataGrid that is checked for errors. This helps to display
        // the error message associated with the DataGrid.
        protected enum CyEDataDrid { Channels }

        public virtual string TabName
        {
            get { return "Empty"; }
        }

        public CyTabWrapper() { }
        public CyTabWrapper(CyParameters parameters)
        {
            m_params = parameters;
            m_errorProvider = new ErrorProvider();
            m_errorProvider.BlinkStyle = ErrorBlinkStyle.NeverBlink;
            this.Dock = DockStyle.Fill;
            this.AutoScroll = true;
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
            string errorMessage = string.Empty;

            if (m_errorProvider != null)
                errs.AddRange(CheckControlForErrors(this.Controls));

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

        #region Controls errors check method(s)
        protected virtual List<CyCustErr> CheckControlForErrors(ControlCollection controls)
        {
            string errorMessage = String.Empty;
            List<CyCustErr> errs = new List<CyCustErr>();
            foreach (Control control in controls)
            {
                // If tab contains DataGrid control, check its cells for errors.
                if (control is DataGridView)
                {
                    if (CheckDataGridForErrors((DataGridView)control))
                    {
                        if (control.Tag != null && (CyEDataDrid)control.Tag == CyEDataDrid.Channels)
                        {
                            errs.Add(new CyCustErr(Resources.ChannelsDataGridContainsError));
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

        protected static bool CheckDataGridForErrors(DataGridView dgv)
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
